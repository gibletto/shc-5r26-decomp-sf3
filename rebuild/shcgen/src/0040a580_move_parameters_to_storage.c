#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0040a580
// name : move_parameters_to_storage
// size : 1811
// sig  : void move_parameters_to_storage(gen_node * node)


int __cdecl move_parameters_to_storage(gen_node *node)

{
  byte psd_flags;
  short sVar1;
  uint uVar2;
  ea *arg_loc;
  ea *home_loc;
  byte bVar3;
  uint uVar4;
  int iVar5;
  psd_op op;
  byte mov_flags;
  short i;
  byte work_reg;
  byte size_code;
  char base_reg;
  uchar ea_kind;
  byte *param_flags;
  undefined4 *param_list;
  int *param_loc;
  short *param_symx;
  
  uVar2 = (uint)(short)(node->symx + 0xb6);
  uVar4 = (int)uVar2 >> 0x1f;
  param_list = (undefined4 *)g_symbol_table[(uVar2 ^ uVar4) - uVar4].size;
  do {
    if (param_list == (undefined4 *)0x0) {
      return;
    }
    i = 0;
    do {
      iVar5 = (int)i;
      param_symx = (short *)((int)param_list + iVar5 * 2 + 8);
      if (*param_symx == -1) break;
      param_flags = (byte *)(iVar5 + 0x10 + (int)param_list);
      if ((*param_flags & 2) == 0) goto LAB_0040ac68;
      psd_flags = 0;
      mov_flags = 0;
      size_code = 0;
      arg_loc = alloc_zeroed(0xc);
      param_loc = param_list + iVar5 + 5;
      if ((*param_flags & 4) == 0) {
        iVar5 = *param_loc;
        base_reg = 'l';
        ea_kind = '\b';
      }
      else {
        base_reg = (char)*param_loc;
        iVar5 = 0;
        ea_kind = '\x01';
      }
      fill_ea(arg_loc,ea_kind,base_reg,-1,'\0',iVar5,(label_ref *)0x0);
      uVar2 = (int)*param_symx >> 0x1f;
      switch(g_symbol_table[((int)*param_symx ^ uVar2) - uVar2].type & 0xfc) {
      case 0:
        size_code = 0;
        mov_flags = 0;
        break;
      case 4:
        size_code = 0;
        goto LAB_0040a6b5;
      case 8:
        size_code = 1;
        mov_flags = 0;
        break;
      case 0xc:
        size_code = 1;
        goto LAB_0040a6b5;
      case 0x10:
      case 0x18:
      case 0x28:
      case 0x30:
      case 0x38:
        size_code = 2;
        mov_flags = 0;
        break;
      case 0x14:
      case 0x1c:
      case 0x40:
        size_code = 2;
LAB_0040a6b5:
        mov_flags = 0x40;
        break;
      default:
        report_codegen_message(0x121b,1,0,0,(char *)0x0);
      }
      uVar2 = (int)*param_symx >> 0x1f;
      if ((g_symbol_table[((int)*param_symx ^ uVar2) - uVar2].type & 2) != 0) {
        psd_flags = 0x80;
      }
      home_loc = alloc_zeroed(0xc);
      uVar2 = (int)*param_symx >> 0x1f;
      iVar5 = ((int)*param_symx ^ uVar2) - uVar2;
      if (g_symbol_table[iVar5].storage.type == '\x01') {
        fill_ea(home_loc,'\x01',g_symbol_table[iVar5].storage.base,-1,'\0',0,(label_ref *)0x0);
        mov_flags = mov_flags | 0x80;
      }
      else {
        fill_ea(home_loc,'\b','l',-1,'\0',g_symbol_table[iVar5].storage.disp,(label_ref *)0x0);
      }
      uVar2 = (int)*param_symx >> 0x1f;
      copy_ea_into(&g_symbol_table[((int)*param_symx ^ uVar2) - uVar2].storage,arg_loc);
      bVar3 = home_loc->type & 0x1f;
      if ((bVar3 == 1) && ((arg_loc->type & 0x1f) == 1)) {
        sVar1 = g_request->cpu;
        if ((sVar1 == 4) &&
           (uVar2 = (int)*param_symx >> 0x1f,
           (g_symbol_table[((int)*param_symx ^ uVar2) - uVar2].type & 0xf8) == 0x30)) {
          base_reg = home_loc->base;
          fill_ea(home_loc,'\x01',base_reg + -0x10,-1,'\0',0,(label_ref *)0x0);
          fill_ea(arg_loc,'\x01',(char)*param_loc + -0x10,-1,'\0',0,(label_ref *)0x0);
          psd_flags = psd_flags | 2;
          fill_psd_record((psd *)&g_psd_scratch,OP_NON_B0,psd_flags,mov_flags,g_stmt_serial,
                          g_msg_filn,g_msg_line,home_loc,arg_loc,0,-1);
          emit_psd_record((psd *)&g_psd_scratch,0);
          home_loc = alloc_zeroed(0xc);
          fill_ea(home_loc,'\x01',base_reg + -0xf,-1,'\0',0,(label_ref *)0x0);
          arg_loc = alloc_zeroed(0xc);
          fill_ea(arg_loc,'\x01',(char)*param_loc + -0xf,-1,'\0',0,(label_ref *)0x0);
          work_reg = 0xff;
          op = OP_NON_B0;
          iVar5 = 0;
        }
        else {
          if ((sVar1 == 2) && (g_request->fpu_mode == '\x03')) {
            bVar3 = 1;
          }
          else {
            bVar3 = -(sVar1 == 4) & 2;
          }
          if ((bVar3 == 0) ||
             (uVar2 = (int)*param_symx >> 0x1f,
             (g_symbol_table[((int)*param_symx ^ uVar2) - uVar2].type & 0xf8) != 0x28)) {
            work_reg = 0xff;
            psd_flags = psd_flags | 2;
            op = OP_MOV;
            iVar5 = 0;
          }
          else {
            work_reg = 0xff;
            psd_flags = psd_flags | 2;
            op = OP_NON_B0;
            iVar5 = 0;
          }
        }
      }
      else {
        if ((g_request->cpu == 4) &&
           (uVar2 = (int)*param_symx >> 0x1f,
           (g_symbol_table[((int)*param_symx ^ uVar2) - uVar2].type & 0xf8) == 0x30)) {
          if (bVar3 == 1) {
            base_reg = home_loc->base;
            iVar5 = arg_loc->disp;
            fill_ea(home_loc,'\x01',base_reg + -0x10,-1,'\0',0,(label_ref *)0x0);
            sVar1 = choose_general_register(0,0,'\0');
            work_reg = (byte)sVar1;
            remove_serial_from_register_ranges(1 << (work_reg & 0x1f),g_stmt_serial);
            fill_psd_record((psd *)&g_psd_scratch,OP_MOV_LOC,psd_flags | size_code,mov_flags,
                            g_stmt_serial,g_msg_filn,g_msg_line,home_loc,arg_loc,g_sptravel,work_reg
                           );
            emit_psd_record((psd *)&g_psd_scratch,0);
            home_loc = alloc_zeroed(0xc);
            fill_ea(home_loc,'\x01',base_reg + -0xf,-1,'\0',0,(label_ref *)0x0);
            arg_loc = alloc_zeroed(0xc);
            iVar5 = (char)iVar5 + 4;
            base_reg = 'l';
            ea_kind = '\b';
          }
          else {
            base_reg = arg_loc->base;
            iVar5 = home_loc->disp;
            fill_ea(arg_loc,'\x01',base_reg + -0x10,-1,'\0',0,(label_ref *)0x0);
            sVar1 = choose_general_register(0,0,'\0');
            work_reg = (byte)sVar1;
            remove_serial_from_register_ranges(1 << (work_reg & 0x1f),g_stmt_serial);
            fill_psd_record((psd *)&g_psd_scratch,OP_MOV_LOC,psd_flags | size_code,mov_flags,
                            g_stmt_serial,g_msg_filn,g_msg_line,home_loc,arg_loc,g_sptravel,work_reg
                           );
            emit_psd_record((psd *)&g_psd_scratch,0);
            home_loc = alloc_zeroed(0xc);
            base_reg = base_reg + -0xf;
            fill_ea(home_loc,'\b','l',-1,'\0',(char)iVar5 + 4,(label_ref *)0x0);
            arg_loc = alloc_zeroed(0xc);
            iVar5 = 0;
            ea_kind = '\x01';
          }
          fill_ea(arg_loc,ea_kind,base_reg,-1,'\0',iVar5,(label_ref *)0x0);
          sVar1 = choose_general_register(0,0,'\0');
          work_reg = (byte)sVar1;
          remove_serial_from_register_ranges(1 << (work_reg & 0x1f),g_stmt_serial);
        }
        else {
          sVar1 = choose_general_register(0,0,'\0');
          work_reg = (byte)sVar1;
          remove_serial_from_register_ranges(1 << (work_reg & 0x1f),g_stmt_serial);
        }
        psd_flags = psd_flags | size_code;
        op = OP_MOV_LOC;
        iVar5 = g_sptravel;
      }
      fill_psd_record((psd *)&g_psd_scratch,op,psd_flags,mov_flags,g_stmt_serial,g_msg_filn,
                      g_msg_line,home_loc,arg_loc,iVar5,work_reg);
      emit_psd_record((psd *)&g_psd_scratch,0);
LAB_0040ac68:
      i = i + 1;
    } while (i < 4);
    param_list = (undefined4 *)*param_list;
  } while( true );
}



