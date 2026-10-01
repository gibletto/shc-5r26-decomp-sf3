#!/bin/sh
# Export one stage from a Ghidra project for tools/regen-<stage>.sh, in read-only sessions: the project is never
# changed, and everything the export uses beyond the analysed executable is applied from ghidra/names/<stage>/ in
# each session (ApplyStageTables.java; see ghidra/names/README.md). Writes:
#   ghidra/reports/<stage>-now    ExportFullDecomp + ExportGlobalTypes
#   ghidra/reports/<stage>-ret4   the functions of ghidra/names/<stage>/ret4-list.txt decompiled with their return
#                                 locked to undefined4; use.txt lists those whose value is not a leftover EAX
# Usage: tools/export-stage-now.sh <stage>
# GHIDRA_HOME: the Ghidra 12.0.4 install; GHIDRA_PROJECT: the directory holding the project (sh5.gpr, the four
# executables imported and analysed with the default analysers; GHIDRA_PROJECT_NAME if not sh5). JAVA_HOME: a JDK 21.
# NAMES_DIR: another tables directory to try (default ghidra/names/<stage>).
set -e
cd "$(dirname "$0")/.."
S=$1
[ -n "$S" ] || { echo "usage: $0 <stage>"; exit 2; }
[ -n "$GHIDRA_HOME" ] && [ -n "$GHIDRA_PROJECT" ] || { echo "set GHIDRA_HOME and GHIDRA_PROJECT"; exit 2; }
w() { cygpath -w "$1"; }
H=$(w "$GHIDRA_HOME/support/analyzeHeadless.bat")
P=$(w "$GHIDRA_PROJECT")
PN=${GHIDRA_PROJECT_NAME:-sh5}
R=ghidra/reports
N=${NAMES_DIR:-ghidra/names/$S}
export JAVA_TOOL_OPTIONS="-Xmx256m"     # the launcher's JDK probe only; Ghidra's own -Xmx comes later and wins
rm -rf $R/$S-now $R/$S-ret4
mkdir -p $R/$S-now $R/$S-ret4/decomp
run() {   # run <log> <script args...>: one read-only session on <stage>.exe with the tables applied
  log=$1; shift
  cmd.exe //c "$H $P $PN -process $S.exe -noanalysis -readOnly -scriptPath $(w ghidra/scripts) \
    -postScript ApplyStageTables.java $(w "$N") $*" < /dev/null > "$log" 2>&1
  grep -q "ApplyStageTables: done" "$log" || { echo "tables not applied, see $log"; exit 1; }
}
run $R/$S-now.log -postScript ExportFullDecomp.java "$(w $R/$S-now)" \
  -postScript ExportGlobalTypes.java "$(w $R/$S-now/global_types.tsv)"
run $R/$S-ret4.log -postScript DecompileAddresses.java "$(w "$N/ret4-list.txt")" "$(w $R/$S-ret4/decomp)" ret4
# use.txt: the functions whose locked return is not a leftover EAX. shcmdl's keeps a short returned in AX
# (CONCAT22(in_EAX >> 16, x)) as a value
if [ "$S" = shcmdl ]; then
  python tools/ret4-candidates.py $S-now --use $S-ret4/decomp > /dev/null
  mv $R/$S-ret4/decomp/use.txt $R/$S-ret4/use.txt
else
  grep -L "in_EAX" $R/$S-ret4/decomp/0*.c | sed 's|.*/||; s|_.*||' > $R/$S-ret4/use.txt
fi
echo "$S: $(ls $R/$S-now/decomp | wc -l) functions exported, $(wc -l < $R/$S-ret4/use.txt) with a locked return"
