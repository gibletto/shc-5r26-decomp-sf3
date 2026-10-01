#include "decls.h"
#include "imports.h"

// entry: 00414710
// name : dump_web_chain
// size : 69
// sig  : void dump_web_chain(dutbl * web, char * title)


int __cdecl dump_web_chain(dutbl *web,char *title)

{
  FID_conflict__wprintf(s___web_chain_print___s____004356d0,title);
  for (; web != (dutbl *)0x0; web = web->next) {
    FID_conflict__wprintf
              (s___CUR_0x_08x__blk_0x_08x____d_____0043569c,web,web->block,(int)web->block->number,
               web->node,(uint)web->node->pp);
  }
  return;
}



