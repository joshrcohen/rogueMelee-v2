import hashlib
from pathlib import Path


def file_hash(path: Path, algorithm: str = "sha256") -> str:
    digest = hashlib.new(algorithm)
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(4 * 1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def review_hash(path: Path) -> str:
    """Portable review-artifact hash: normalize Git text line endings only."""
    data=path.read_bytes()
    if path.suffix in ('.c','.h','.py','.toml','.json','.md','.csv','.log'):
        data=data.replace(b'\r\n',b'\n')
    return hashlib.sha256(data).hexdigest()
