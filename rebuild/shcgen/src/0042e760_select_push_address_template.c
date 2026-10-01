#include "decls.h"
#include "imports.h"

// entry: 0042e760
// name : select_push_address_template
// size : 190
// sig  : tmpl_header * select_push_address_template(ea * src, ea * temp)


tmpl_header * __cdecl select_push_address_template(ea *src,ea *temp)

{
  tmpl_header *tmpl;
  byte src_kind;
  tmpl_header *local_4;
  
  src_kind = src->type & 0x1f;
  if (src_kind == 0xd) {
    return (tmpl_header *)&g_tmpl_apusha001;
  }
  if (((src_kind == 2) && (src->base == 'l')) || ((src_kind == 8 && (src->base == 'l')))) {
    return (tmpl_header *)&g_tmpl_apusha002;
  }
  if (src_kind == 9) {
    if (src->index == temp->base) {
      return (tmpl_header *)&g_tmpl_apusha006;
    }
    tmpl = (tmpl_header *)&g_tmpl_apusha007;
    if (src->base != temp->base) {
      return (tmpl_header *)&g_tmpl_apusha008;
    }
  }
  else {
    if ((src_kind != 2) && (src_kind != 8)) {
      report_codegen_message(0x122a,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      return local_4;
    }
    if ((src->labels == (label_ref *)0x0) && (src->disp == 0)) {
      return (tmpl_header *)&g_tmpl_apusha003;
    }
    tmpl = (tmpl_header *)&g_tmpl_apusha004;
  }
  return tmpl;
}



