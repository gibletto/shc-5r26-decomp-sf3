#!/usr/bin/env python3
"""Turn Ghidra-only spellings in a C rebuild's sources into C:

- X._n_m_  (m bytes at byte offset n of X, Ghidra's partial access)  ->  (*(T *)((char *)&X + n)), T by m
  (m = 3: an unsigned int masked to 24 bits, read-only)
- string labels holding characters C identifiers cannot (s_<name>_00428db8, s_a>b_004270e8)  ->  s_str_<address>
- xRamNNNNNNNN (Ghidra's name for a fixed low address, a NULL-pointer field on a dead path)  ->  (*(T *)0xNNNNNNNN)
- a label or case label right before }  ->  followed by an empty statement
- switch((T *)x) / case (T *)0xN:  (a switch on a pointer-typed variable)  ->  switch((int)x) / case 0xN:
- FILE fields: the streams the stage opens are the host CRT's (src/_crt_shim.c), whose FILE a newer CRT keeps
  private: &f->_ptr -> f, the EOF and error flags -> feof(f) / ferror(f). The stock CRT's own stream table
  (stock_piob) holds stock records: FILE -> GhFILE there.

Usage: python tools/ghidra-c-spellings.py <stage>
"""
import re, sys
from pathlib import Path

R = Path(__file__).resolve().parent.parent / "rebuild" / sys.argv[1] / "src"
PIECE = {1: "unsigned char", 2: "unsigned short", 4: "unsigned int", 8: "unsigned __int64"}
RAM = {"s": "short", "u": "unsigned short", "i": "int", "b": "unsigned char", "c": "char", "p": "int", "pc": "char *", "pg": "gen_node *"}   # pg: shcgen's gen_node *
n = 0
for f in R.glob("0*.c"):
    s = f.read_bytes().decode("latin-1")
    o = s

    def piece(m):
        base, off, size = m.group(1), int(m.group(2)), int(m.group(3))
        if size == 3:
            return f"(*(unsigned int *)((char *)&{base} + {off}) & 0xffffff)"
        return f"(*({PIECE.get(size, 'unsigned int')} *)((char *)&{base} + {off}))"
    s = re.sub(r"\b([A-Za-z_]\w*(?:\.[A-Za-z_]\w*)*)\._(\d+)_(\d+)_\b", piece, s)
    s = re.sub(r"\b[su]_[^\s,;()\[\]]*?[<>][^\s,;()\[\]]*?_([0-9a-f]{8})\b", lambda m: f"s_str_{m.group(1)}", s)
    s = re.sub(r"\b([a-z]|pc|pg)Ram([0-9a-f]{8})\b", lambda m: f"(*({RAM.get(m.group(1), 'int')} *)0x{m.group(2)})", s)
    # x = <fixed low address>; if (p != 0) { x = p->f; }: the machine reads (p ? p : 0)->f once, so the low address
    # is read only when p is 0; Ghidra hoists that read above the test, which the C would do every time
    s = re.sub(r"(\n[ \t]*)(\w+) = (\(\*\([\w *]+\)0x[0-9a-f]{8}\));(\r?\n[ \t]*)if \(([^\n]*)\) \{\r?\n[ \t]*\2 = ([^\n]*);"
               r"\r?\n[ \t]*\}", r"\1if (\5) {\1  \2 = \6;\1}\1else {\1  \2 = \3;\1}", s)
    s = re.sub(r"(\n[ \t]*[A-Za-z_]\w*:)([ \t]*\r?\n[ \t]*\})", r"\1 ;\2", s)     # a label before } needs a statement
    s = re.sub(r"(\n[ \t]*(?:case [^\n]+?|default):)([ \t]*\r?\n[ \t]*\})", r"\1 ;\2", s)    # so does a case label
    # a switch on a pointer-typed variable (Ghidra keeps its type): switch on the int, plain case constants
    s = re.sub(r"\bswitch\(\((?:unsigned |signed )?\w+ \*\)", "switch((int)", s)
    s = re.sub(r"\bcase \((?:unsigned |signed )?\w+ \*\)(0x[0-9a-fA-F]+|\d+):", r"case \1:", s)
    s = re.sub(r"&(\w+)->_ptr\b", r"\1", s)
    s = re.sub(r"\((\w+)->_flag & 0x10U?\) != 0", r"feof(\1)", s)
    s = re.sub(r"\((\w+)->_flag & 0x20U?\) == 0", r"!ferror(\1)", s)
    if "stock_piob" in s:
        s = re.sub(r"\bFILE\b", "GhFILE", s)
    if s != o:
        f.write_bytes(s.encode("latin-1"))
        n += 1
print(n, "files rewritten")
