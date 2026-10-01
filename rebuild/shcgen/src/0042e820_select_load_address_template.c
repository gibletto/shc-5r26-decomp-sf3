#include "decls.h"
#include "imports.h"

// entry: 0042e820
// name : select_load_address_template
// size : 267
// sig  : tmpl_header * select_load_address_template(ea * src, ea * dst)


tmpl_header * __cdecl select_load_address_template(ea *src,ea *dst)

{
  byte src_kind;
  tmpl_header *tmpl;
  tmpl_header *local_4;
  
  if ((dst->type & 0x1f) != 1) {
    src_kind = src->type & 0x1f;
    if (((src_kind == 2) ||
        (((src_kind == 8 && (src->disp == 0)) && (src->labels == (label_ref *)0x0)))) &&
       (src->base != 'l')) {
      return (tmpl_header *)&g_tmpl_alda008;
    }
    return (tmpl_header *)&g_tmpl_alda007;
  }
  src_kind = src->type & 0x1f;
  if (src_kind == 0xd) {
    return (tmpl_header *)&g_tmpl_alda001;
  }
  if (((src_kind != 2) || (src->base != 'l')) && ((src_kind != 8 || (src->base != 'l')))) {
    if (src_kind == 9) {
      tmpl = (tmpl_header *)&g_tmpl_alda009;
      if (dst->base != src->base) {
        return (tmpl_header *)&g_tmpl_alda010;
      }
    }
    else {
      if ((src_kind != 2) && (src_kind != 8)) {
        report_codegen_message(0x122b,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
        return local_4;
      }
      if (src->labels == (label_ref *)0x0) {
        if (src->disp == 0) {
          return (tmpl_header *)&g_tmpl_alda003;
        }
        if ((-0x81 < src->disp) && (src->disp < 0x80)) {
          return (tmpl_header *)&g_tmpl_alda004;
        }
      }
      tmpl = (tmpl_header *)&g_tmpl_alda006;
      if (dst->base != src->base) {
        tmpl = (tmpl_header *)&g_tmpl_alda005;
      }
    }
    return tmpl;
  }
  return (tmpl_header *)&g_tmpl_alda002;
}



