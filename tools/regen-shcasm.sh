#!/bin/sh
# Regenerate rebuild/shcasm/src from the Ghidra export tools/export-stage-now.sh shcasm makes (ghidra/reports/
# shcasm-now and shcasm-ret4, with the tables of ghidra/names/shcasm applied). Hand-written sources (src/_*.c but
# _relocs.c, _stubs.c) are kept.
set -e
cd "$(dirname "$0")/.."
EXP=shcasm-now
# the stock CRT's stdio and its helpers are replaced by src/_crt_shim.c over the host CRT (as in shcpep, plus
# fseek/fgets/ftell, which shcasm calls on its temp files); 0043a990 is a second copy of memcpy that nothing calls
# (0043a960, the second _strncnt, is compiled: __crtLCMapStringA calls it by its own name); 004391b0
# GetCurrentProcessId and 0043abf8 RtlUnwind are import thunks; 00435660 is the CRT entry (src/_stubs.c has main)
CRT="004355b0 004353c0 004354d0 004357a0 004358f0 00436120 00435cd0 00435ec0 00435f10 004360f0 004351c0 00435220
     00435b30 00436540 004365e0 00436780 00437160 004371b0 004371f0 00437270 00437340 004375f0 00437800 00437970
     004379b2 00438389 004383b0 00437880 00436630 00438c90 004394f0 00439bb0 00439780 00439c50 00439dc0 00435020
     00435430 004355f0 00437440
"
python tools/gen-stage-types.py shcasm                          # include/stage_types.h from ghidra/names/shcasm
python tools/new-rebuild-sources.py shcasm $EXP --skip 0043a990 004391b0 0043abf8 00435660 --crt $CRT
addrs=$(ls rebuild/shcasm/src/0*.c | sed 's|.*/||; s|_.*||')
EXPORT=$EXP python tools/import-ghidra-function.py shcasm $addrs > /dev/null
# functions Ghidra left with an unlocked 'undefined' return, decompiled again with the return locked to undefined4
# (DecompileAddresses.java ... ret4); those whose value would be a leftover EAX (in_EAX) are really void and stay out
EXPORT=shcasm-ret4 python tools/import-ghidra-function.py shcasm $(for a in $(cat ghidra/reports/shcasm-ret4/use.txt); do
    ls rebuild/shcasm/src/${a}_*.c >/dev/null 2>&1 && echo $a; done) > /dev/null
sed -i 's/(code \*)0x0\b/0/g' rebuild/shcasm/src/0*.c        # VC6: a null code pointer compare needs a plain 0
python tools/ghidra-c-spellings.py shcasm
python tools/raw-data-literals.py shcasm --apply | tail -1      # stock data addresses left as numbers -> SD()
python tools/scaffold-rebuild.py shcasm --heap stock_crtheap --reports $EXP
python tools/apply-global-types.py shcasm ghidra/reports/$EXP/global_types.tsv
python tools/frame-records.py shcasm --all --stack-arrays --locals ghidra/names/shcasm/locals.tsv | tail -1
python tools/mixed-sign-bytes.py shcasm --apply | tail -1   # char vs byte ==: Ghidra compares bytes, C promotes
python tools/negative-compares.py shcasm --apply | tail -1  # untyped byte == -1: Ghidra compares bits, C promotes
python tools/extraout-calls.py shcasm --apply | tail -1     # extraout_EAX: the value the call before it returned
python tools/fold-byte-copies.py shcasm          # a record field copied byte by byte -> one assignment
python tools/shcasm-fixes.py
# LF line endings whatever Python wrote (a Windows Python writes CRLF in text mode)
sed -i 's/\r$//' rebuild/shcasm/src/0*.c rebuild/shcasm/src/_relocs.c rebuild/shcasm/src/_stubs.c rebuild/shcasm/src/_stockdata.c \
  rebuild/shcasm/include/decls.h rebuild/shcasm/include/imports.h rebuild/shcasm/include/ghidra_stubs.h \
  rebuild/shcasm/include/stage_types.h rebuild/shcasm/include/stage_types.names
