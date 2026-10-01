#include "decls.h"
#include "imports.h"

// entry: 004201e0
// name : find_section_record
// size : 58
// sig  : request_section * find_section_record(request * req, short section_no)


request_section * __cdecl find_section_record(request *req,short section_no)

{
  request_section *section;
  
  section = req->sections;
  if (section != (request_section *)0x0) {
    do {
      if (section->id == section_no) break;
      section = section->next;
    } while (section != (request_section *)0x0);
    if (section != (request_section *)0x0) {
      return section;
    }
  }
  report_compiler_message(0,0,0x12ed,(char *)0x0);
  return (request_section *)0x0;
}



