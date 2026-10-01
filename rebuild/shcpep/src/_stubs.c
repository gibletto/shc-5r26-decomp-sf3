#include "decls.h"
#include "imports.h"

extern void _stockdata_relocate(void);

int main(int argc, char **argv) {
    _stockdata_relocate();
    stock_crtheap = (int)GetProcessHeap();
    shcpep_main(argc, (int)argv);
    return 0;
}
