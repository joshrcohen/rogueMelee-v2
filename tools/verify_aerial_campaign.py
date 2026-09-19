"""Recheck archived native logs and publish the aerial release acceptance gate."""
import gzip
import hashlib
import json
import re
import subprocess
from lib.config import ROOT
from lib.emulator import verify_aerial_log, verify_extended_log, verify_match_log, verify_special_log
from lib.hash import review_hash
from aerial_report import generate

BASELINE='490f3f6314879ebb5dddd82032daead2e5b962d5'
FOLDER=ROOT/'docs/evidence/aerials/current'


def read(name):
    path=FOLDER/(name+'.json')
    result=json.loads(path.read_text())
    raw=gzip.decompress(path.with_suffix('.log.gz').read_bytes())
    if result['status']!='pass' or hashlib.sha256(raw).hexdigest()!=result['log_sha256']:
        raise ValueError('Invalid archived result: '+name)
    return result,raw.decode(errors='replace')


def main():
    results=[]
    for start,count in [(0,728),(728,728),(1456,624),(2080,624)]:
        result,log=read(f'specials-full-current-{start}-{count}')
        assert verify_special_log(log,start,count)
        results.append(result)
    result,log=read('specials-regression-0-104')
    assert verify_extended_log(log,0,104)
    results.append(result)
    for name in ('matches-regression-0-100','aerials-disabled-0-100'):
        result,log=read(name)
        assert verify_match_log(log,100)
        if 'disabled' in name: assert result['build']['aerials'] is False
        results.append(result)
    for name,stress,new_fixture in [
        ('aerials-debug-stress-0-130',True,False),
        ('aerials-release-extended-0-130',False,False),
        ('aerials-debug-current-0-130',False,True),
        ('aerials-release-stress-0-130',True,True)]:
        result,log=read(name)
        assert verify_aerial_log(log,0,130,True,stress)
        indices=[(i%26)*130+(i//26)*26+i%26 if stress else i for i in range(130)]
        if new_fixture:
            native=[tuple(map(int,r)) for r in re.findall(r'aerial_native_slots index=(\d+) checked=(\d+) valid=(\d+)',log)]
            assert native==[(i,0 if stress else 4,1) for i in indices]
            adapter=[tuple(map(int,r)) for r in re.findall(r'aerial_adapter index=(\d+) valid=(\d+)',log)]
            assert adapter==[(i,1) for i in indices if i%130 in (15,17,18,34,109)]
        results.append(result)
    fixture='src/platform/melee/qa/special_matrix.c'
    original=subprocess.check_output(['git','show',BASELINE+':'+fixture],cwd=ROOT).decode().replace('\r\n','\n')
    assert (ROOT/fixture).read_text()==original, 'Baseline special fixture changed'
    generate()
    paths=list(FOLDER.glob('*'))+list((ROOT/'docs/compatibility').glob('aerials.*'))
    sources=[p for p in (ROOT/'src').rglob('*') if p.suffix in ('.c','.h')]
    sources += [p for p in (ROOT/'integration').glob('*') if p.is_file()]
    record=dict(status='pass',scenario='aerials-validation',baseline_commit=BASELINE,
        special_cases=2704,special_extended_cases=104,match_transitions=100,
        disabled_match_transitions=100,aerial_cases=520,
        baseline_special_fixture_unchanged=True,
        coverage='Two 130-case aerial schedules, each in debug and release; schedules overlap. See compatibility report for unique exact combinations. Null special matrix is logic-only; aerial campaigns are rendered.',
        legacy_freeze='Unreproduced; no claim of diagnosis or fix',
        campaigns=[dict(scenario=r['scenario'],profile=r['build']['profile'],start=r['start'],iterations=r['iterations'],seconds=r['seconds'],backend=r.get('video_backend','profile-default'),dol_sha1=r['build']['dol_sha1']) for r in results],
        review_hash_format='SHA256, CRLF normalized to LF for text artifacts; raw bytes for compressed logs and other binary files',
        artifact_sha256={p.relative_to(ROOT).as_posix():review_hash(p) for p in sorted(paths)},
        source_sha256={p.relative_to(ROOT).as_posix():review_hash(p) for p in sorted(sources)})
    (ROOT/'docs/qa/aerials-validation.json').write_text(json.dumps(record,indent=2)+'\n')
    print('PASS: archived aerial campaign, adapters, unchanged special fixture and compatibility report')


if __name__=='__main__': main()
