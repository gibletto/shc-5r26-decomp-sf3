#include "decls.h"
#include "imports.h"

extern void _stockdata_relocate(void);

int main(int argc, char **argv) {
    _stockdata_relocate();
    stock_crtheap = (int)HeapCreate(1, 0x1000, 0);
    optimizer_main(argc, (int)argv);
    return 0;
}
