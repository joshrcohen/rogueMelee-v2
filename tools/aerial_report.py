"""Publish every recipient/donor/slot, retaining build-specific evidence."""
import csv
import gzip
import hashlib
import json
import re
from pathlib import Path
from lib.config import ROOT
from lib.debug_launch import CHARACTERS


def generate():
    catalog = json.loads((ROOT/'data/aerials.json').read_text())
    evidence = {}
    # Only archived, reviewed campaign inputs certify current compatibility.
    # Historical failures remain in the investigation directory, not silently
    # promoted to passes by whichever unrelated file was written most recently.
    for path in sorted((ROOT/'docs/evidence/aerials/current').glob('aerials-*.json')):
        result = json.loads(path.read_text())
        if not result.get('build',{}).get('qa_aerials'): continue
        log_path = path.with_suffix('.log')
        compressed = path.with_suffix('.log.gz')
        raw = gzip.decompress(compressed.read_bytes()) if compressed.exists() else log_path.read_bytes()
        if hashlib.sha256(raw).hexdigest() != result.get('log_sha256'):
            raise ValueError('Evidence hash mismatch: '+str(path))
        log = raw.decode(errors='replace')
        seen=set()
        for index, won, entries, cleanups, failures in re.findall(
                r'aerial_result index=(\d+) won=(\d+) entries=(\d+) cleanups=(\d+) failures=(\d+)',log):
            index = int(index)
            seen.add(index)
            passed = (won, entries, cleanups, failures) == ('1','2','2','0')
            record = dict(status='runtime-tested' if passed else 'failing',
                profile=result['build']['profile'],
                lifecycle=bool(result['build'].get('qa_lifecycle')),
                stress=bool(result['build'].get('qa_aerial_stress')),
                native_jab='aerial_native_slots' in log,
                adapter_assertion=bool(re.search(r'aerial_adapter index='+str(index)+r' valid=1\b',log)),
                backend=result.get('video_backend','profile-default'),
                dol_sha1=result['build']['dol_sha1'],
                evidence=path.relative_to(ROOT).as_posix(),
                log_sha256=result['log_sha256'])
            evidence.setdefault(index,[]).append(record)
        cases=[int(i) for i in re.findall(r'aerial_case index=(\d+)',log)]
        if result['status']=='failed' and cases and cases[-1] not in seen:
            evidence.setdefault(cases[-1],[]).append(dict(status='failing',
                profile=result['build']['profile'],lifecycle=bool(result['build'].get('qa_lifecycle')),
                dol_sha1=result['build']['dol_sha1'],evidence=path.relative_to(ROOT).as_posix(),
                log_sha256=result['log_sha256'],reason=result.get('error','Incomplete case')))
    rows=[]
    for recipient in range(26):
        for move in catalog:
            index=recipient*130+move['id']-1
            tests=evidence.get(index,[])
            status='failing' if any(t['status']=='failing' for t in tests) else 'runtime-tested' if tests else 'untested'
            rows.append(dict(index=index,recipient=CHARACTERS[recipient],donor=CHARACTERS[move['character']],
                slot=['nair','fair','bair','uair','dair'][move['slot']],implementation='implemented',
                runtime_status=status,offer_eligible=recipient!=move['character'],
                adapter='gamewatch-articles' if move['character']==3 and move['slot'] in (0,2,3) else 'link-down-bounce' if move['character'] in (6,21) and move['slot']==4 else 'common-aerial',
                exclusion_reason='Identical donor: keep the native slot' if recipient==move['character'] else '',
                evidence=tests))
    folder=ROOT/'docs/compatibility';folder.mkdir(exist_ok=True)
    (folder/'aerials.json').write_text(json.dumps(dict(
        baseline='490f3f6314879ebb5dddd82032daead2e5b962d5',
        scope='Entry, donor animation table, landing rate with/without L-cancel, shared ownership restoration. Extended cases add damage, grab, ledge, death and respawn. Stress adds five equipped slots, four specials, three opponents, repeated stocks, encounter equipment changes and transformations. Additional slot entries in stress are not counted as full lifecycle coverage. No claim of every hitbox or visual matchup.',
        combinations=rows),indent=2)+'\n')
    with (folder/'aerials.csv').open('w',newline='') as stream:
        writer=csv.DictWriter(stream,fieldnames=list(rows[0]));writer.writeheader()
        for row in rows: writer.writerow({**row,'evidence':json.dumps(row['evidence'],separators=(',',':'))})
    counts={label:sum(r['runtime_status']==label for r in rows) for label in ('runtime-tested','failing','untested')}
    lines=['# Borrowed aerial compatibility','',
        'All 26 playable recipients × 26 playable donors × 5 aerial slots are enumerated in [CSV](aerials.csv) and [JSON](aerials.json). Implementation and runtime validation are separate fields. Each tested row links to archived native evidence and executable/log hashes.','',
        f"Implemented: **3380**. Runtime-tested: **{counts['runtime-tested']}**. Failing in the accepted campaign: **{counts['failing']}**. Untested: **{counts['untested']}**.",'',
        '“Implemented” means the generic runtime or named adapter exists; it is not a runtime pass. “Runtime-tested” means the listed controlled lifecycle assertions passed on the recorded executable. “Failing” means an accepted campaign case failed. “Untested” means no accepted full lifecycle case for that exact pair/slot. “Unsupported” is reserved for excluded configurations; none of these 3380 playable combinations is currently classified unsupported. Independent Nana, non-playable boss forms, partner borrowing and other game revisions are outside this table and unsupported.','',
        'The 130 identical recipient/donor choices are intentionally excluded from offers: an unequipped slot already provides that native move. Other implemented choices remain eligible, including rows explicitly labeled untested. There is no native fallback reported as a successful borrowed entry.','',
        'Coverage checks entry, animation ownership, donor landing rates with/without L-cancel, mixed special transitions, damage, linked grabs, ledges, death and respawn. Stress additionally covers five slots, four specials, three opponents, repeated stocks/equipment changes and transformations. These checks do not certify every visual effect, hitbox, collision, stage or long-duration matchup. Game & Watch article and Link/Young Link bounce adapter assertions are identified per evidence record. Ice Climbers rows cover the leader.','',
        '| Recipient | Runtime-tested | Failing | Untested |','| --- | ---: | ---: | ---: |']
    for recipient in CHARACTERS:
        subset=[r for r in rows if r['recipient']==recipient]
        values=[sum(r['runtime_status']==label for r in subset) for label in ('runtime-tested','failing','untested')]
        lines.append('| '+recipient+' | '+' | '.join(map(str,values))+' |')
    lines += ['', 'Regenerate from the archived current campaign: `py -3 tools/aerial_report.py`. Historical failures and their specific repairs are documented in [the investigation](../aerials-investigation.md).','']
    (folder/'aerials.md').write_text('\n'.join(lines),encoding='utf-8')
    print(json.dumps(counts))


if __name__=='__main__': generate()
