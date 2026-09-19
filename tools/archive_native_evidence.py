"""Archive passing native results with lossless, hash-verified compressed logs."""
import argparse
import gzip
import hashlib
import json
from pathlib import Path
from lib.config import ROOT


def archive(source, destination):
    source = Path(source)
    result = json.loads(source.read_text())
    if result.get('status') != 'pass':
        raise ValueError('Only passing campaign evidence belongs in current: '+str(source))
    raw = source.with_suffix('.log').read_bytes()
    if hashlib.sha256(raw).hexdigest() != result['log_sha256']:
        raise ValueError('Native log changed: '+str(source))
    destination = Path(destination)
    destination.mkdir(parents=True, exist_ok=True)
    (destination/source.name).write_text(json.dumps(result, indent=2)+'\n')
    (destination/source.with_suffix('.log.gz').name).write_bytes(gzip.compress(raw,mtime=0))
    print('Archived '+source.name)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('results',nargs='+',type=Path)
    parser.add_argument('--destination',type=Path,default=ROOT/'docs/evidence/aerials/current')
    args = parser.parse_args()
    for result in args.results: archive(result,args.destination)
