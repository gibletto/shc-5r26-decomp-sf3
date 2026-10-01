#!/bin/sh
# Regenerate rebuild/shcmdl/src from the Ghidra export tools/export-stage-now.sh shcmdl makes (ghidra/reports/
# shcmdl-now and shcmdl-ret4, with the tables of ghidra/names/shcmdl applied). The function set is chosen by
# select-functions.py: reachable from optimizer_main (00401000) or from the stock data, minus the CRT routines
# src/_crt_shim.c takes from the host CRT. Hand-written sources (src/_*.c but _relocs.c, _stubs.c) are kept.
set -e
cd "$(dirname "$0")/.."
EXP=shcmdl-now
python tools/gen-stage-types.py shcmdl                          # include/stage_types.h from ghidra/names/shcmdl
SHIM="FID_conflict___toupper_lk _fclose __fsopen FID_conflict__wprintf FID_conflict__fwprintf _fflush __flush _sprintf
      _fputc _fputs _signal _rewind __fread_lk stock_fwrite_lk _tmpnam __global_unwind2 __local_unwind2 __isctype __close
      __access __FF_MSGBANNER ___crtMessageBoxA __chsize stock_alloca_probe __setjmp3 _longjmp __ftol stock_fseek stock_flsbuf stock_ftell"
python tools/select-functions.py shcmdl --export $EXP --root 401000 --crt 4296f0 --shim $SHIM --write | head -1
addrs=$(ls rebuild/shcmdl/src/0*.c | sed 's|.*/||; s|_.*||')
EXPORT=$EXP python tools/import-ghidra-function.py shcmdl $addrs > /dev/null
# functions Ghidra left with an unlocked 'undefined' return whose callers use the result, decompiled again with the
# return locked to undefined4 (DecompileAddresses.java ... ret4); those whose value would be a leftover EAX (in_EAX)
# are really void and stay out of use.txt
if [ -f ghidra/reports/shcmdl-ret4/use.txt ]; then
  use=$(for a in $(cat ghidra/reports/shcmdl-ret4/use.txt); do ls rebuild/shcmdl/src/${a}_*.c > /dev/null 2>&1 && echo $a; done)
  EXPORT=shcmdl-ret4 python tools/import-ghidra-function.py shcmdl $use > /dev/null
fi
sed -i 's/(code \*)0x0\b/0/g' rebuild/shcmdl/src/0*.c        # VC6: a null code pointer compare needs a plain 0
# the upper bytes of a call's byte/short result (CONCAT31(extraout_var, b)): 0, as the stock callees leave them
sed -i -E 's/^(\s+undefined[0-9]? extraout_var(_[0-9]+)?);/\1 = 0;/' rebuild/shcmdl/src/0*.c
# Ghidra's -0x80000000 is INT_MIN; in C it is the unsigned 0x80000000 (and makes the comparison unsigned)
sed -i 's/-0x80000000\b/(-0x7fffffff - 1)/g' rebuild/shcmdl/src/0*.c
python tools/ghidra-c-spellings.py shcmdl
python tools/raw-data-literals.py shcmdl --apply | tail -1      # stock data addresses left as numbers -> SD()
python tools/scaffold-rebuild.py shcmdl --heap stock_crtheap --heap-create --main optimizer_main --reports $EXP
python tools/apply-global-types.py shcmdl ghidra/reports/$EXP/global_types.tsv --underscore
python tools/frame-records.py shcmdl --all --locals ghidra/names/shcmdl/locals.tsv | tail -1
python tools/stack-refs.py shcmdl | tail -1        # stack0xN: frame ends and parameter slots
python tools/mixed-sign-bytes.py shcmdl --apply | tail -1   # char vs byte ==: Ghidra compares bytes, C promotes
python tools/narrow-negative-compares.py shcmdl --apply | tail -1   # undefined2 x == -1 is a 16-bit compare
python tools/fold-byte-copies.py shcmdl          # a record field copied byte by byte -> one assignment
python tools/shcmdl-fixes.py
# LF line endings whatever Python wrote (a Windows Python writes CRLF in text mode)
sed -i 's/\r$//' rebuild/shcmdl/src/0*.c rebuild/shcmdl/src/_relocs.c rebuild/shcmdl/src/_stubs.c rebuild/shcmdl/src/_stockdata.c \
  rebuild/shcmdl/include/decls.h rebuild/shcmdl/include/imports.h rebuild/shcmdl/include/ghidra_stubs.h \
  rebuild/shcmdl/include/stage_types.h rebuild/shcmdl/include/stage_types.names
