#include "decls.h"
#include "imports.h"

// entry: 00428140
// name : find_section_by_id
// size : 109
// sig  : request_section * find_section_by_id(request * req, short id)


request_section * __cdecl find_section_by_id(request *req,short id)

{
  request_section *found_section;
  
  for (found_section = req->sections;
      (found_section != (request_section *)0x0 && (found_section->id != id));
      found_section = found_section->next) {
  }
  if (found_section == (request_section *)0x0) {
    report_message_at_source_line(0,0,0x12ed,(char *)0x0);
  }
  return found_section;
}



