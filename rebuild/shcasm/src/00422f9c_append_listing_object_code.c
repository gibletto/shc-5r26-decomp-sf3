#include "decls.h"
#include "imports.h"

// entry: 00422f9c
// name : append_listing_object_code
// size : 571
// sig  : void __cdecl append_listing_object_code(int value,short nbytes,short relocatable)


int __cdecl append_listing_object_code(int value,short nbytes,short relocatable)

{
  short chunk_bytes;
  int room_bytes;
  char nbytes_before;
  
  do {
    if (nbytes < 1) {
      return;
    }
    if (relocatable != 0) {
      nbytes = nbytes + 1;
      if (g_listing_code_column_pos != 0) {
        g_listing_code_column_pos = g_listing_code_column_pos + 1;
      }
      if ((10 - g_listing_code_column_pos) / 2 < (int)nbytes) {
        g_listing_code_column_pos = 10;
      }
    }
    if ((10 - g_listing_code_column_pos) / 2 == 0) {
      if (0xfe < g_listing_code_row_last) {
        return;
      }
      g_listing_code_row_last = g_listing_code_row_last + 1;
      for (g_listing_code_column_pos = 0; g_listing_code_column_pos < 10;
          g_listing_code_column_pos = g_listing_code_column_pos + 1) {
        (&g_listing_code_rows)[g_listing_code_row_last * 10 + (int)g_listing_code_column_pos] = 0x20
        ;
      }
      g_listing_code_column_pos = 0;
    }
    if ((10 - g_listing_code_column_pos) / 2 < (int)nbytes) {
      room_bytes = (10 - g_listing_code_column_pos) / 2;
      chunk_bytes = (short)room_bytes;
      nbytes_before = (char)nbytes;
      nbytes = nbytes - chunk_bytes;
      format_hex_digits(value >> ((nbytes_before - (char)room_bytes) * '\b' & 0x1fU),chunk_bytes,
                        &g_listing_code_rows +
                        (int)g_listing_code_column_pos + g_listing_code_row_last * 10);
      g_listing_code_column_pos = g_listing_code_column_pos + chunk_bytes * 2;
    }
    else {
      if (relocatable != 0) {
        (&g_listing_code_rows)[g_listing_code_row_last * 10 + (int)g_listing_code_column_pos] = 0x3c
        ;
        g_listing_code_column_pos = g_listing_code_column_pos + 1;
        nbytes = nbytes + -1;
      }
      format_hex_digits(value,nbytes,
                        &g_listing_code_rows +
                        (int)g_listing_code_column_pos + g_listing_code_row_last * 10);
      g_listing_code_column_pos = g_listing_code_column_pos + nbytes * 2;
      nbytes = 0;
      if (relocatable != 0) {
        (&g_listing_code_rows)[g_listing_code_row_last * 10 + (int)g_listing_code_column_pos] = 0x3e
        ;
        g_listing_code_column_pos = g_listing_code_column_pos + 2;
      }
    }
  } while( true );
}
