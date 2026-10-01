#!/bin/sh
# Regenerate rebuild/shcpep/src from the Ghidra export tools/export-stage-now.sh shcpep makes (ghidra/reports/
# shcpep-now and shcpep-ret4, with the tables of ghidra/names/shcpep applied). The function set is the 0*.c files
# already in src/ (renamed after the export). Hand-written sources (src/_*.c but _relocs.c, _stubs.c) are kept.
set -e
cd "$(dirname "$0")/.."
EXP=shcpep-now
python tools/gen-stage-types.py shcpep                          # include/stage_types.h from ghidra/names/shcpep
python tools/rename-rebuild-sources.py shcpep $EXP              # src/<addr>_<name>.c after the export's names
addrs=$(ls rebuild/shcpep/src/0*.c | sed 's|.*/||; s|_.*||')
EXPORT=$EXP python tools/import-ghidra-function.py shcpep $addrs > /dev/null
# functions Ghidra left with an unlocked 'undefined' return (a bare return;) whose callers use EAX, decompiled again
# with the return locked to undefined4 (DecompileAddresses.java ... ret4); those whose value would be a leftover EAX
# (in_EAX) are really void and stay out of use.txt
EXPORT=shcpep-ret4 python tools/import-ghidra-function.py shcpep $(cat ghidra/reports/shcpep-ret4/use.txt) > /dev/null
sed -i 's/(code \*)0x0\b/0/g' rebuild/shcpep/src/0*.c        # VC6: a null code pointer compare needs a plain 0
python tools/ghidra-c-spellings.py shcpep
python tools/raw-data-literals.py shcpep --apply | tail -1      # stock data addresses left as numbers -> SD()
python tools/scaffold-rebuild.py shcpep --heap stock_crtheap --reports $EXP
python tools/apply-global-types.py shcpep ghidra/reports/$EXP/global_types.tsv
python tools/frame-records.py shcpep --all --stack-names --locals ghidra/names/shcpep/locals.tsv | tail -1
python tools/mixed-sign-bytes.py shcpep --apply | tail -1   # char vs byte ==: Ghidra compares bytes, C promotes
python tools/fold-byte-copies.py shcpep          # a record field copied byte by byte -> one assignment
python tools/shcpep-fixes.py
# LF line endings whatever Python wrote (a Windows Python writes CRLF in text mode)
sed -i 's/\r$//' rebuild/shcpep/src/0*.c rebuild/shcpep/src/_relocs.c rebuild/shcpep/src/_stubs.c rebuild/shcpep/src/_stockdata.c \
  rebuild/shcpep/include/decls.h rebuild/shcpep/include/imports.h rebuild/shcpep/include/ghidra_stubs.h \
  rebuild/shcpep/include/stage_types.h rebuild/shcpep/include/stage_types.names
