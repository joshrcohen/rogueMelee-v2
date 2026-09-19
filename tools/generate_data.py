"""Generate deterministic C registries from project-owned TOML."""
import json
from pathlib import Path
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def generate():
    specials = json.loads((ROOT/'data/specials.json').read_text())
    if len(specials) != 104 or len({r['id'] for r in specials}) != 104:
        raise ValueError('Special catalog must contain 104 unique definitions')
    lines = ['#include "special_catalog.h"', 'const RogueSpecialDef rogue_specials[ROGUE_SPECIALS] = {']
    for row in specials:
        lines.append('    { ' + ', '.join(json.dumps(row[f]) for f in ['id','character','donor','slot','price','key','name']) + ' },')
    (ROOT/'src/combat/specials/special_catalog_data.c').write_text('\n'.join(lines + ['};','']))
    economy = tomllib.loads((ROOT / 'data/balance.toml').read_text())['economy']
    header = '#ifndef ROGUE_BALANCE_H\n#define ROGUE_BALANCE_H\n'
    for key, value in economy.items():
        if not isinstance(value, int) or value < 0:
            raise ValueError('Invalid economy integer: ' + key)
        header += f'#define ROGUE_{key.upper()} {value}U\n'
    for key, value in tomllib.loads((ROOT/'data/balance.toml').read_text())['score'].items():
        if not isinstance(value,int) or value < 0: raise ValueError('Invalid score integer')
        header += f'#define ROGUE_SCORE_{key.upper()} {value}U\n'
    (ROOT / 'src/core/balance.h').write_text(header + '#endif\n')
    for name, array, ctype, fields in [
        ('upgrades','rogue_upgrades','RogueUpgradeDef',['key','name','description','price','max_stacks','stat','amount']),
        ('encounters','rogue_recipes','RogueRecipe',['key','name','rule','tier','enemies','tags','damage','defense','speed','scale','percent','stocks','cooldown','weight','stage_mask'])]:
        rows = tomllib.loads((ROOT / f'data/{name}.toml').read_text())['entry']
        if len({r['key'] for r in rows}) != len(rows):
            raise ValueError('Duplicate registry key')
        folder, stem = ('upgrades','upgrade_registry') if name == 'upgrades' else ('encounters','encounter_registry')
        lines = [f'#include "{stem}.h"', f'const {ctype} {array}[{len(rows)}] = {{']
        for row in rows:
            values = [json.dumps(row[f],ensure_ascii=True) for f in fields]
            if name == 'encounters':
                if len(row['roster']) != 3 or any(v not in range(26) and v != 255 for v in row['roster']):
                    raise ValueError('Encounter roster requires three character IDs or random sentinel 255')
                values.append('{ '+', '.join(map(str,row['roster']))+' }')
            lines.append('    { ' + ', '.join(values) + ' },')
        lines += ['};','']
        (ROOT / f'src/{folder}/{stem}.c').write_text('\n'.join(lines))


if __name__ == '__main__':
    generate()
