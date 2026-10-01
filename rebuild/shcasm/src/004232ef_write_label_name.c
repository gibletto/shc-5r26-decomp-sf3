#include "decls.h"
#include "imports.h"

// entry: 004232ef
// name : write_label_name
// size : 356
// sig  : void __cdecl write_label_name(short stream,short label,short field)


int __cdecl write_label_name(short stream,short label,short field)

{
  symbol *sym;
  
  if (label < 0) {
    put_char_at_column(stream,'-',field);
    label = -label;
  }
  if (label == -0x8000) {
    put_text_at_column(stream,s__STARTOF_004419bc,field);
    put_text_at_column(stream,&s_dollar_G0_004419c8,field);
    put_text_at_column(stream,&s_rp_004419cc,field);
  }
  else {
    sym = find_symbol_by_id(label);
    if ((sym->flags & 0x80) == 0) {
      put_char_at_column(stream,'L',field);
      write_decimal(stream,(int)label,field);
      if (field == 0) {
        put_char_at_column(stream,':',0);
        g_new_symbol_count = g_new_symbol_count + 1;
      }
    }
    else {
      put_char_at_column(stream,'_',field);
      stock_strcpy((uint *)&g_label_name_buffer,(uint *)sym->name);
      if (field == 0) {
        stock_strcat((uint *)&g_label_name_buffer,(uint *)&DAT_004419b8);
      }
      put_text_at_column(stream,&g_label_name_buffer,field);
    }
  }
  return;
}
