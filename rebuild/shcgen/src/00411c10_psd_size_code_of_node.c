#include "decls.h"
#include "imports.h"

// entry: 00411c10
// name : psd_size_code_of_node
// size : 32
// sig  : uchar psd_size_code_of_node(gen_node * node)


uchar __cdecl psd_size_code_of_node(gen_node *node)

{
  int size;
  
  size = node_value_size(node);
  if (size == 1) {
    return '\0';
  }
  if (size != 2) {
    return '\x02';
  }
  return '\x01';
}



