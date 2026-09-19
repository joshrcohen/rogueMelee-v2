"""Deterministic Dolphin DTM controller fixtures (Dolphin 2606a Movie.h format)."""
import struct
from pathlib import Path
from .hash import file_hash


def write_ui_movie(image, destination):
    # Holds span several emulated polls, unlike transient OS keyboard events.
    pulses = [(300, 310, 4), (350, 360, 4), (400, 410, 8),
              (450, 460, 1 << 9), (500, 510, 2),
              (600, 610, 1 << 9), (650, 660, 2)]
    count = 1000
    header = bytearray(256)
    header[:4] = b'DTM\x1a'
    header[4:10] = b'GALE01'
    header[11] = 1
    struct.pack_into('<Q',header,13,count)
    struct.pack_into('<Q',header,21,count)
    author = b'rogueMelee QA\0'
    header[49:49 + len(author)] = author
    header[113:129] = bytes.fromhex(file_hash(Path(image),'md5'))
    struct.pack_into('<Q',header,129,1789833600)
    for offset in (137,138,139,141,142,143,144,145,148,151): header[offset] = 1
    header[163] = 49
    struct.pack_into('<Q',header,237,count*8100000)
    frames = bytearray()
    for i in range(count):
        buttons = 0x4000
        for begin,end,mask in pulses:
            if begin <= i < end: buttons |= mask
        frames += struct.pack('<H6B',buttons,0,0,128,128,128,128)
    destination = Path(destination)
    assert len(header) == 256
    assert len(frames) == count * 8
    destination.parent.mkdir(parents=True,exist_ok=True)
    destination.write_bytes(header+frames)
    return destination
