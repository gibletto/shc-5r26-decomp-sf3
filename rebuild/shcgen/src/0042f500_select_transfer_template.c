#include "decls.h"
#include "imports.h"

// entry: 0042f500
// name : select_transfer_template
// size : 400
// sig  : tmpl_header * select_transfer_template(int forced, uint kind, ea * src, ea * dst, ea * extra, char type, char reg, gen_node * node)


tmpl_header * __cdecl
select_transfer_template
          (int forced,uint kind,ea *src,ea *dst,ea *extra,char type,char reg,gen_node *node)

{
  short sVar1;
  tmpl_header *ptVar2;
  bool bVar3;
  tmpl_header *local_4;
  
  if (forced != 0) {
    switch(kind) {
    case 1:
      ptVar2 = select_load_template(src,dst,extra,type);
      return ptVar2;
    case 2:
      ptVar2 = select_store_template(src,dst,extra,type);
      return ptVar2;
    case 3:
      ptVar2 = select_load_address_template(src,dst);
      return ptVar2;
    case 4:
      ptVar2 = select_push_address_template(src,extra);
      return ptVar2;
    case 5:
      ptVar2 = select_move_template(type,src,dst,node);
      return ptVar2;
    case 6:
      ptVar2 = select_push_template(type,src,reg,node);
      return ptVar2;
    default:
      report_codegen_message(0x122e,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      return local_4;
    }
  }
  sVar1 = ea_operands_equal(src,dst);
  if (sVar1 != 0) {
    return (tmpl_header *)0x0;
  }
  if ((src->type & 0x40) != 0) {
    if (kind == 1) {
      kind = 3;
    }
    else {
      bVar3 = kind == 6;
      if (!bVar3) goto LAB_0042f655;
      kind = 4;
    }
  }
  bVar3 = kind == 6;
LAB_0042f655:
  if (5 < kind && !bVar3) {
    report_codegen_message(0x122f,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return local_4;
  }
                    /* WARNING: Could not recover jumptable at 0x0042f657. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  switch (kind) {
  case 0:
    if ((dst->type & 0x1f) == 3 && dst->base == 0x0f) {
      if ((src->type & 0x40) != 0) return select_push_address_template(src,extra);
      return select_push_template(type,src,reg,node);
    }
    if ((dst->type & 0x1f) == 1) {
      if ((src->type & 0x40) != 0) return select_load_address_template(src,dst);
      return select_load_template(src,dst,extra,type);
    }
    if ((src->type & 0x1f) == 1) return select_store_template(src,dst,extra,type);
    if ((src->type & 0x40) != 0) return select_load_address_template(src,dst);
    return select_move_template(type,src,dst,node);
  case 1: return select_load_template(src,dst,extra,type);
  case 2: return select_store_template(src,dst,extra,type);
  case 3: return select_load_address_template(src,dst);
  case 4: return select_push_address_template(src,extra);
  case 5: return select_move_template(type,src,dst,node);
  default: return select_push_template(type,src,reg,node);
  }
}



