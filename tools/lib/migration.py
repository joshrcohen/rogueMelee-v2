"""Inventory the prepared legacy oracle; never use its patch chain to build."""
import hashlib
import json
import re
import subprocess
from .config import ROOT
from .deps import ensure


def inventory():
    legacy = ensure('legacy-specials')
    prepared = [p for p in (legacy / '.cache').glob('melee-*') if (p / '.rogue-prepared').exists()]
    if len(prepared) != 1:
        raise ValueError('Prepare the pinned legacy oracle first; expected one .rogue-prepared checkout')
    oracle = prepared[0]
    diff = subprocess.check_output(['git','diff','--no-ext-diff','--unified=0'],cwd=oracle,text=True,stderr=subprocess.DEVNULL)
    records = []
    for block in diff.split('diff --git ')[1:]:
        path = re.search(r'^a/(.*?) b/',block).group(1)
        for part in re.split(r'(?m)^@@ ',block)[1:]:
            location,body=part.split('\n',1)
            changes='\n'.join(line for line in body.splitlines() if line.startswith(('+','-')))
            categories=[]
            if any(token in changes for token in ['Rogue_Aerial','rogue_aerial']): categories.append('excluded-aerial')
            if 'Rogue_AbilityVars' in changes: categories.append('donor-variable-bank')
            if any(token in changes for token in ['Rogue_AbilityMapBone','Rogue_AbilityData','ftParts_GetBoneIndex','ftPartsRemap']): categories.append('bone-animation-data')
            if 'Rogue_AbilityMotionState' in changes or 'new_motion_state != NULL' in changes: categories.append('state-table-redirect')
            if 'Rogue_AbilityCleanup' in changes or 'Rogue_AbilityFighterDestroyed' in changes: categories.append('lifecycle-cleanup')
            if 'Rogue_AbilityFighterCreated' in changes: categories.append('donor-preload')
            if 'Rogue_BorrowedTransform' in changes or 'Rogue_AbilityTransformed' in changes or 'Rogue_AbilityClimberPartner' in changes: categories.append('transform-subfighter')
            if 'Rogue_TrySpecial' in changes: categories.append('special-input')
            if 'Rogue_IsAbilityState' in changes or 'Rogue_AbilitySourceKind' in changes: categories.append('donor-compatibility')
            if 'rogue_ability.h' in changes: categories.append('special-interface')
            if not categories:
                if path.startswith(('src/melee/gm/','src/melee/mn/','src/melee/gr/','src/Runtime/')) or path=='configure.py':
                    categories=['excluded-legacy-build-flow']
                elif any(t in changes for t in ['Rogue_Modify','Rogue_ApplyMovement','RogueEffects_','RogueItem_','RogueAI_','rogue_ai.h','rogue_effects.h','rogue_items.h','rogue_hooks.h']):
                    categories=['excluded-legacy-modifier']
                elif path.endswith('ftafterimage.c'):
                    categories=['bone-animation-data']
                elif path.endswith('ftkirby.c') and 'vars->kb.' in changes:
                    categories=['donor-variable-bank']
                elif path.endswith('ftgamewatch.c') and 'costume' in changes:
                    categories=['donor-compatibility']
                elif path.endswith('ftyoshi.c') and 'fp->kind != Ft_Kind_Yoshi' in changes:
                    categories=['donor-compatibility']
                elif path.endswith('ftcoll.c') and changes.strip()=='+                }':
                    categories=['excluded-legacy-modifier']
                elif 'rogueSurviveBlastZone' in changes or 'authored_jump' in changes or 'shield_max' in changes:
                    categories=['excluded-legacy-modifier']
                else:
                    categories=['REVIEW']
            records.append(dict(file=path,hunk=location,sha256=hashlib.sha256(changes.encode()).hexdigest(),categories=categories,changes=changes))
    output=ROOT/'build/migration'; output.mkdir(parents=True,exist_ok=True)
    (output/'specials-source-map.json').write_text(json.dumps(records,indent=2)+'\n')
    lines=['# Special migration diff inventory','',
           'Generated from the pinned prepared oracle. Classification is evidence inventory, not proof that an adapter has been ported or tested.', '',
           '| File and hunk | Categories | Port status |','| --- | --- | --- |']
    for r in records:
        lines.append('| `'+r['file']+'` '+r['hunk'].replace('|','/')+' | '+', '.join(r['categories'])+' | '+('Excluded' if all(x.startswith('excluded-') for x in r['categories']) else 'Pending')+' |')
    (ROOT/'docs/migration/specials-diff-inventory.md').write_text('\n'.join(lines)+'\n')
    remaining=[r for r in records if 'REVIEW' in r['categories']]
    print(f'Inventoried {len(records)} hunks; {len(remaining)} require manual classification')
    if remaining:
        raise ValueError('Unclassified legacy changes remain; inspect build/migration/specials-source-map.json')
    return records
