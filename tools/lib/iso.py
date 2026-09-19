"""Read-only verification of the exact supported retail image."""
import hashlib
import json
import struct
from pathlib import Path
from .hash import file_hash

ISO_MD5 = "0e63d4223b01d9aba596259dc155a174"
DOL_SHA1 = "08e0bf20134dfcb260699671004527b2d6bb1a45"


def read_dol(image):
    with Path(image).open("rb") as stream:
        header = stream.read(0x440)
        if len(header) != 0x440 or header[:6] != b"GALE01" or header[7] != 2:
            raise ValueError("Expected GALE01 NTSC-U revision 1.02 disc header")
        offset = struct.unpack_from(">I", header, 0x420)[0]
        stream.seek(offset)
        dol_header = stream.read(0x100)
        if len(dol_header) != 0x100:
            raise ValueError("Truncated DOL header")
        offsets = struct.unpack_from(">18I", dol_header, 0)
        sizes = struct.unpack_from(">18I", dol_header, 0x90)
        length = max([0x100] + [o + s for o, s in zip(offsets, sizes) if s])
        if length > Path(image).stat().st_size - offset:
            raise ValueError("DOL section outside image")
        stream.seek(offset)
        return stream.read(length)


def verify(image, root):
    image = Path(image).resolve()
    if not image.is_file():
        raise ValueError(f"Image does not exist: {image}; set MELEE_ISO_PATH")
    print(f"Verifying read-only source: {image}", flush=True)
    md5 = file_hash(image, "md5")
    if md5 != ISO_MD5:
        raise ValueError(f"Unsupported image MD5 {md5}; expected {ISO_MD5}")
    dol = read_dol(image)
    sha1 = hashlib.sha1(dol).hexdigest()
    if sha1 != DOL_SHA1:
        raise ValueError(f"Unsupported DOL SHA1 {sha1}; expected {DOL_SHA1}")
    manifest = dict(image=str(image), game_id="GALE01", revision=2,
                    bytes=image.stat().st_size, md5=md5, dol_sha1=sha1,
                    dol_bytes=len(dol))
    output = root / "build/source-manifest.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    return manifest
