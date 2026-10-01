#include "decls.h"
#include "imports.h"

// entry: 0040fae0
// name : find_section_record
// size : 58
// sig  : request_section * find_section_record(request * req, short section_no)


request_section * __cdecl find_section_record(request *req,short section_no)

{
  request_section *sect;
  
  sect = req->sections;
  if (sect != (request_section *)0x0) {
    do {
      if (sect->id == section_no) break;
      sect = sect->next;
    } while (sect != (request_section *)0x0);
    if (sect != (request_section *)0x0) {
      return sect;
    }
  }
  report_compiler_message(0,0,0x12ed,(char *)0x0);
  return (request_section *)0x0;
}



