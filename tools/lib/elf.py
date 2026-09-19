"""Minimal read-only ELF32 big-endian symbol inspection for target QA."""
import struct


class Elf:
    def __init__(self, path):
        self.data=path.read_bytes()
        if self.data[:6] != b'\x7fELF\x01\x02':
            raise ValueError('Expected ELF32 big-endian target')
        offset=struct.unpack_from('>I',self.data,32)[0]
        size,count=struct.unpack_from('>HH',self.data,46)
        self.sections=[struct.unpack_from('>10I',self.data,offset+i*size) for i in range(count)]
        self.symbols={}
        for section in self.sections:
            if section[1]!=2: continue
            strings=self.sections[section[6]]
            table=self.data[strings[4]:strings[4]+strings[5]]
            for i in range(section[4],section[4]+section[5],section[9]):
                name,value,length,info,other,index=struct.unpack_from('>IIIBBH',self.data,i)
                if name:
                    key=table[name:table.find(b'\0',name)].decode('utf-8',errors='replace')
                    self.symbols[key]=(value,length,index)

    def read(self, address, length):
        for s in self.sections:
            if s[1]!=8 and s[3]<=address and address+length<=s[3]+s[5]:
                start=s[4]+address-s[3]
                return self.data[start:start+length]
        raise ValueError('ELF address is not backed by file data')

    def string(self, address):
        out=bytearray()
        for i in range(256):
            char=self.read(address+i,1)
            if char==b'\0': return out.decode('ascii')
            out.extend(char)
        raise ValueError('Unterminated registry string')
