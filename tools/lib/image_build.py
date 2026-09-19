"""Place a grown executable without overwriting the retail FST or file data."""
import shutil
import struct
from pathlib import Path


def layout(stream):
    stream.seek(0x420)
    dol, fst, size, maximum = struct.unpack('>4I', stream.read(16))
    stream.seek(fst)
    table = stream.read(size)
    if len(table) != size or size < 12 or table[0] != 1:
        raise ValueError('Invalid disc filesystem table')
    count = struct.unpack_from('>I', table, 8)[0]
    if count < 1 or count * 12 > size:
        raise ValueError('Invalid disc filesystem entry count')
    ranges = [(0, 0x2440), (fst, fst + maximum)]
    stream.seek(0x2454)
    loader, trailer = struct.unpack('>II', stream.read(8))
    ranges.append((0x2440, 0x2460 + loader + trailer))
    stream.seek(dol)
    header = stream.read(256)
    offsets = struct.unpack_from('>18I', header)
    lengths = struct.unpack_from('>18I', header, 0x90)
    ranges.append((dol, dol + max(256, *(a + b for a, b in zip(offsets, lengths) if b))))
    for i in range(1, count):
        kind, start, length = struct.unpack_from('>III', table, i * 12)
        if not kind >> 24:
            ranges.append((start, start + length))
    return table, sorted(ranges)


def assemble(source, dol, output):
    source, dol, output = map(Path, (source, dol, output))
    if output.resolve() in (source.resolve(), dol.resolve()):
        raise ValueError('Output must differ from all inputs')
    image_size = source.stat().st_size
    executable = dol.read_bytes()
    with source.open('rb') as stream:
        table, ranges = layout(stream)
    cursor = 0
    destination = None
    for start, end in ranges + [(image_size, image_size)]:
        cursor = (cursor + 31) & ~31
        if start - cursor >= len(executable):
            destination = cursor
            break
        cursor = max(cursor, end)
    if destination is None:
        raise ValueError('No safe in-disc extent for rebuilt executable')
    output.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(source, output)
    with output.open('r+b') as stream:
        stream.seek(destination)
        stream.write(executable)
        stream.seek(0x420)
        stream.write(struct.pack('>I', destination))
    with output.open('rb') as stream:
        actual, _ = layout(stream)
    if actual != table:
        raise ValueError('Filesystem changed during executable assembly')
    print(f'Executable placed at 0x{destination:08x}; retail FST preserved ({len(table)} bytes)')
    return destination
