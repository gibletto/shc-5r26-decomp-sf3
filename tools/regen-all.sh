#!/bin/sh
# Regenerate the four stages' C from Release 26 (extracted/bin, tools/setup.py) with Ghidra 12.0.4.
# Usage: tools/regen-all.sh [stage ...]
# GHIDRA_HOME: the Ghidra 12.0.4 install; JAVA_HOME: a JDK 21. GHIDRA_PROJECT: the project directory (default
# ghidra/project); if it holds no project yet, one is made: the four executables imported with the default analysis.
# Then each stage is exported (tools/export-stage-now.sh) and regenerated (tools/regen-<stage>.sh).
set -e
cd "$(dirname "$0")/.."
[ -n "$GHIDRA_HOME" ] || { echo "set GHIDRA_HOME"; exit 2; }
export GHIDRA_PROJECT=${GHIDRA_PROJECT:-ghidra/project}
export JAVA_TOOL_OPTIONS="-Xmx256m"     # the launcher's JDK probe only
STAGES=${*:-shcmdl shcgen shcpep shcasm}
if [ ! -f "$GHIDRA_PROJECT/sh5.gpr" ]; then
  mkdir -p "$GHIDRA_PROJECT"
  for s in shcmdl shcgen shcpep shcasm; do
    echo "importing $s.exe"
    cmd.exe //c "$(cygpath -w "$GHIDRA_HOME/support/analyzeHeadless.bat") $(cygpath -w "$GHIDRA_PROJECT") sh5 \
      -import $(cygpath -w extracted/bin/$s.exe)" < /dev/null > "$GHIDRA_PROJECT/import-$s.log" 2>&1 || true
    grep -q "Import succeeded" "$GHIDRA_PROJECT/import-$s.log" || { echo "import failed, see $GHIDRA_PROJECT/import-$s.log (remove $GHIDRA_PROJECT before trying again)"; exit 1; }
  done
fi
for s in $STAGES; do
  sh tools/export-stage-now.sh $s
  sh tools/regen-$s.sh > ghidra/reports/regen-$s.log 2>&1 || { echo "regen failed, see ghidra/reports/regen-$s.log"; exit 1; }
  echo "$s: regenerated"
done
