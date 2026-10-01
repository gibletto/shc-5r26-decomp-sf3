#include "decls.h"
#include "imports.h"

// entry: 00418360
// name : displacement_ok_for_dereference
// size : 378
// sig  : short displacement_ok_for_dereference(gen_node * node, int forced)


short __cdecl displacement_ok_for_dereference(gen_node *node,int forced)

{
  gen_node *access;
  byte bVar1;
  short ok;
  byte bVar2;
  byte access_type;
  node_desc *desc;
  int offset;
  bool under_aster;
  bool walking;
  
  ok = 0;
  under_aster = false;
  walking = true;
  desc = node->desc;
  offset = (desc->value).disp;
  for (access = node->parent; access != (gen_node *)0x0; access = access->parent) {
    switch(access->op) {
    case IL_CAST:
    case IL_ADD:
    case IL_SUB:
      bVar2 = access->type & 0xf8;
      if ((((bVar2 != 0x40) && (bVar2 != 0x10)) && (bVar2 != 0x18)) &&
         ((access->type & 0xe0) != 0x80)) goto switchD_00418399_caseD_21;
      break;
    case IL_ASTER:
      under_aster = true;
    default:
switchD_00418399_caseD_21:
      walking = false;
    }
    if (!walking) break;
  }
  if (!under_aster) {
    bVar2 = (desc->value).type & 0x1f;
    if (((bVar2 == 2) && ((desc->value).base == 'l')) ||
       ((bVar2 == 8 && ((desc->value).base == 'l')))) {
      ok = 1;
    }
    return ok;
  }
  if ((desc->value).labels != (label_ref *)0x0) {
    return 1;
  }
  if (forced != 0) {
    return 1;
  }
  bVar2 = (desc->value).type & 0x1f;
  if (((bVar2 == 2) || (bVar2 == 8)) && ((desc->value).base != 'l')) {
    access_type = access->type;
    bVar1 = access_type & 0xf8;
    if ((((((access_type & 0xf8) == 0) && (((-1 < offset && (offset < 0x10)) || (0x7f < offset))))
         || (((access_type & 0xf8) == 8 && (((-1 < offset && (offset < 0x1f)) || (0x7f < offset)))))
         ) || ((((bVar1 == 0x10 || (bVar1 == 0x18)) || ((bVar1 == 0x28 || (bVar1 == 0x40)))) &&
               (((-1 < offset && (offset < 0x3d)) || (0x7f < offset)))))) ||
       ((((access_type & 0xe0) != 0 && (bVar1 != 0x28)) && ((bVar1 != 0x40 && (-1 < offset))))))
    goto LAB_00418495;
  }
  if (((bVar2 != 2) || ((desc->value).base != 'l')) && ((bVar2 != 8 || ((desc->value).base != 'l')))
     ) {
    return 0;
  }
LAB_00418495:
  ok = displacement_aligned_for_type(access,(uchar)offset);
  return ok;
}



