#!/bin/sh
# Regenerate rebuild/shcgen/src from the Ghidra export tools/export-stage-now.sh shcgen makes (ghidra/reports/
# shcgen-now and shcgen-ret4, with the tables of ghidra/names/shcgen applied). Hand-written sources are kept:
# src/_regknobs.c (the rules and the register-choice trace), src/_remaprules.c (GEN_CHAIN_JUMP and its log),
# src/_r0varrules.c (GEN_R0VAR), src/_poolrules.c (GEN_POOL_MOVLOC), src/_reloadrules.c (GEN_RELOAD),
# src/_evictrules.c (GEN_EVICT_ORDER), src/_crt_shim.c (the stock CRT stdio, replaced
# by the host CRT).
set -e
cd "$(dirname "$0")/.."
EXP=shcgen-now
# The function set is chosen by select-functions.py: reachable from shcgen_main (0041a860) or from the stock data
# (00405310, a handler-table entry Ghidra's analysis missed, is made a function by ghidra/names/shcgen/entries.tsv),
# minus the CRT routines src/_crt_shim.c takes from the host CRT
SHIM="_fclose _fflush _fputc _fputs _rewind _sprintf _tmpnam __fread_lk __fsopen __flush __getbuf __chsize __close
      ___crtMessageBoxA __isctype _signal stock_fwrite stock_fseek stock_doexit"
python tools/gen-stage-types.py shcgen                          # include/stage_types.h from ghidra/names/shcgen
python tools/select-functions.py shcgen --export $EXP --root 41a860 --crt 43a5d0 --shim $SHIM --write | sed -n 1p
addrs=$(ls rebuild/shcgen/src/0*.c | sed 's|.*/||; s|_.*||')
EXPORT=$EXP python tools/import-ghidra-function.py shcgen $addrs > /dev/null
# functions Ghidra left with an unlocked 'undefined' return whose callers use EAX, decompiled again with the return
# locked to undefined4 (DecompileAddresses.java ... ret4); those whose value would be a leftover EAX (in_EAX) are
# really void and stay out of use.txt
EXPORT=shcgen-ret4 python tools/import-ghidra-function.py shcgen $(for a in $(cat ghidra/reports/shcgen-ret4/use.txt); do
    ls rebuild/shcgen/src/${a}_*.c >/dev/null 2>&1 && echo $a; done) > /dev/null
sed -i 's/(code \*)0x0\b/0/g' rebuild/shcgen/src/0*.c        # VC6: a null code pointer compare needs a plain 0
# the upper bytes of a call's byte/short result (CONCAT31(extraout_var, b)): 0, as the stock callees leave them
sed -i -E 's/^(\s+undefined[0-9]? extraout_var(_[0-9]+)?);/\1 = 0;/' rebuild/shcgen/src/0*.c
python tools/ghidra-c-spellings.py shcgen
python tools/raw-data-literals.py shcgen --apply | tail -1      # stock data addresses left as numbers -> SD()
python tools/scaffold-rebuild.py shcgen --heap stock_crtheap --main shcgen_main --reports $EXP
python tools/apply-global-types.py shcgen ghidra/reports/$EXP/global_types.tsv
python tools/frame-records.py shcgen --all --stack-names --locals ghidra/names/shcgen/locals.tsv | tail -1
python tools/mixed-sign-bytes.py shcgen --apply | tail -1   # char vs byte ==: Ghidra compares bytes, C promotes
python tools/negative-compares.py shcgen --apply | tail -1  # untyped byte == -1: Ghidra compares bits, C promotes
python tools/extraout-calls.py shcgen --apply | tail -1     # extraout_EAX: the value the call before it returned
python tools/shcgen-fixes.py
# LF line endings whatever Python wrote (a Windows Python writes CRLF in text mode)
sed -i 's/\r$//' rebuild/shcgen/src/0*.c rebuild/shcgen/src/_relocs.c rebuild/shcgen/src/_stubs.c rebuild/shcgen/src/_stockdata.c \
  rebuild/shcgen/include/decls.h rebuild/shcgen/include/stage_types.h rebuild/shcgen/include/stage_types.names
