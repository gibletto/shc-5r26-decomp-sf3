#include "decls.h"
#include "imports.h"

// entry: 00430250
// name : push_type_piece
// size : 31
// sig  : void __cdecl push_type_piece(char *text,short *count)


int __cdecl push_type_piece(char *text,short *count)

{
  char *piece_text;
  
  piece_text = alloc_type_piece_string(text);
  g_demangle_type_pieces[*count].text = piece_text;
  *count = *count + 1;
  return;
}
