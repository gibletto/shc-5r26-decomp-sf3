#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_demangle_cv_suffix
#define g_demangle_cv_suffix (*(unsigned char *)(g_sd + 0xa4b0))
#undef g_work_buffer_a
#define g_work_buffer_a (*(char * *)(g_sd + 0x14f70))
#undef g_work_buffer_b
#define g_work_buffer_b (*(char * *)(g_sd + 0x14f80))


// entry: 0042f330
// name : demangle_cpp_symbol_name
// size : 1863
// sig  : short demangle_cpp_symbol_name(char * mangled, char * * demangled)


short __cdecl demangle_cpp_symbol_name(char *mangled,char **demangled)

{
  unsigned char _frec_408[1032];
#define local_408 (*(uint *)(_frec_408 + 0))
#define sig_len (*(int *)(_frec_408 + 4))
#define func_name (*(uchar (*)[256])(_frec_408 + 8))
#define cv_codes (*(char (*)[256])(_frec_408 + 264))
#define class_code (*(ushort (*)[128])(_frec_408 + 520))
#define class_name (*(char (*)[256])(_frec_408 + 776))
  char cVar1;
  uchar uVar2;
  ushort sig_kind;
  ushort uVar3;
  short name_code;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  char *pcVar9;
  char *pcVar10;
  char *pcVar11;
  bool found_sig;
  
  found_sig = false;
  (*(unsigned char *)((char *)&g_demangle_cv_suffix + 0)) = 0;
  cv_codes[0] = '\0';
  func_name[0] = '\0';
  class_code[0] = class_code[0] & 0xff00;
  g_demangle_class_scope = 0;
  class_name[0] = '\0';
  iVar4 = reset_work_buffer(1);
  if (iVar4 == -1) {
    return -1;
  }
  iVar4 = reset_work_buffer(2);
  if (iVar4 == -1) {
    return -1;
  }
  if ((*mangled != '_') || (mangled[1] != '_')) {
    return -1;
  }
  iVar4 = 0;
  sig_kind = class_code[0];
  do {
    if (mangled[iVar4 + 1] == '_') {
      uVar2 = mangled[iVar4 + 2];
      if (uVar2 == '_') {
        sig_kind = parse_mangled_signature_kind
                             (mangled + iVar4 + 3,(char *)class_code,cv_codes,&sig_len);
        if (sig_kind == 0) {
          func_name[iVar4] = '\0';
          found_sig = true;
          iVar4 = iVar4 + 3;
          break;
        }
        if (((((sig_kind == 1) || (sig_kind == 2)) || (sig_kind == 3)) ||
            ((sig_kind == 4 || (sig_kind == 5)))) || ((sig_kind == 6 || (sig_kind == 7)))) {
          func_name[iVar4] = '\0';
          found_sig = true;
          iVar4 = iVar4 + sig_len + 3;
          break;
        }
        uVar2 = mangled[iVar4 + 2];
        if (uVar2 == '\0') break;
        func_name[iVar4] = mangled[iVar4 + 1];
        func_name[iVar4 + 1] = uVar2;
        iVar4 = iVar4 + 2;
      }
      else {
        if (uVar2 == '\0') break;
        func_name[iVar4] = '_';
        func_name[iVar4 + 1] = uVar2;
        iVar4 = iVar4 + 2;
      }
    }
    else {
      func_name[iVar4] = mangled[iVar4 + 1];
      iVar4 = iVar4 + 1;
    }
  } while (mangled[iVar4 + 1] != '\0');
  if (!found_sig) {
    return -1;
  }
  if (((sig_kind == 5) || (sig_kind == 6)) || (sig_kind == 7)) {
    iVar5 = 0;
    cVar1 = cv_codes[0];
    while (cVar1 != '\0') {
      if (cv_codes[iVar5] == 'C') {
        uVar6 = 0xffffffff;
        pcVar9 = s_const_suffix;
        do {
          pcVar11 = pcVar9;
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          pcVar11 = pcVar9 + 1;
          cVar1 = *pcVar9;
          pcVar9 = pcVar11;
        } while (cVar1 != '\0');
        uVar6 = ~uVar6;
        iVar7 = -1;
        pcVar9 = (char *)&g_demangle_cv_suffix;
        do {
          pcVar10 = pcVar9;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar10 = pcVar9 + 1;
          cVar1 = *pcVar9;
          pcVar9 = pcVar10;
        } while (cVar1 != '\0');
        pcVar9 = pcVar11 + -uVar6;
        pcVar11 = pcVar10 + -1;
        for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
          pcVar9 = pcVar9 + 4;
          pcVar11 = pcVar11 + 4;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar11 = *pcVar9;
          pcVar9 = pcVar9 + 1;
          pcVar11 = pcVar11 + 1;
        }
        if (cv_codes[iVar5 + 1] != '\0') {
          local_408 = 0xffffffff;
          pcVar9 = (char *)&s_space;
          do {
            pcVar11 = pcVar9;
            if (local_408 == 0) break;
            local_408 = local_408 - 1;
            pcVar11 = pcVar9 + 1;
            cVar1 = *pcVar9;
            pcVar9 = pcVar11;
          } while (cVar1 != '\0');
          local_408 = ~local_408;
          iVar7 = -1;
          pcVar9 = (char *)&g_demangle_cv_suffix;
          do {
            pcVar10 = pcVar9;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar10 = pcVar9 + 1;
            cVar1 = *pcVar9;
            pcVar9 = pcVar10;
          } while (cVar1 != '\0');
          pcVar9 = pcVar11 + -local_408;
          pcVar11 = pcVar10 + -1;
          for (uVar6 = local_408 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
            *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
            pcVar9 = pcVar9 + 4;
            pcVar11 = pcVar11 + 4;
          }
LAB_0042f5e2:
          for (local_408 = local_408 & 3; local_408 != 0; local_408 = local_408 - 1) {
            *pcVar11 = *pcVar9;
            pcVar9 = pcVar9 + 1;
            pcVar11 = pcVar11 + 1;
          }
        }
      }
      else if (cv_codes[iVar5] == 'V') {
        uVar6 = 0xffffffff;
        pcVar9 = s_volatile_suffix;
        do {
          pcVar11 = pcVar9;
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          pcVar11 = pcVar9 + 1;
          cVar1 = *pcVar9;
          pcVar9 = pcVar11;
        } while (cVar1 != '\0');
        uVar6 = ~uVar6;
        iVar7 = -1;
        pcVar9 = (char *)&g_demangle_cv_suffix;
        do {
          pcVar10 = pcVar9;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar10 = pcVar9 + 1;
          cVar1 = *pcVar9;
          pcVar9 = pcVar10;
        } while (cVar1 != '\0');
        pcVar9 = pcVar11 + -uVar6;
        pcVar11 = pcVar10 + -1;
        for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
          pcVar9 = pcVar9 + 4;
          pcVar11 = pcVar11 + 4;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar11 = *pcVar9;
          pcVar9 = pcVar9 + 1;
          pcVar11 = pcVar11 + 1;
        }
        if (cv_codes[iVar5 + 1] != '\0') {
          local_408 = 0xffffffff;
          pcVar9 = (char *)&s_space;
          do {
            pcVar11 = pcVar9;
            if (local_408 == 0) break;
            local_408 = local_408 - 1;
            pcVar11 = pcVar9 + 1;
            cVar1 = *pcVar9;
            pcVar9 = pcVar11;
          } while (cVar1 != '\0');
          local_408 = ~local_408;
          iVar7 = -1;
          pcVar9 = (char *)&g_demangle_cv_suffix;
          do {
            pcVar10 = pcVar9;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar10 = pcVar9 + 1;
            cVar1 = *pcVar9;
            pcVar9 = pcVar10;
          } while (cVar1 != '\0');
          pcVar9 = pcVar11 + -local_408;
          pcVar11 = pcVar10 + -1;
          for (uVar6 = local_408 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
            *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
            pcVar9 = pcVar9 + 4;
            pcVar11 = pcVar11 + 4;
          }
          goto LAB_0042f5e2;
        }
      }
      cVar1 = cv_codes[iVar5 + 1];
      iVar5 = iVar5 + 1;
    }
  }
  if (((((sig_kind == 1) || (sig_kind == 2)) || (sig_kind == 3)) ||
      (((sig_kind == 4 || (sig_kind == 6)) || (sig_kind == 7)))) &&
     (uVar3 = format_class_scope_prefix((char *)class_code,&g_demangle_class_scope,class_name),
     uVar3 != 0)) {
    return -1;
  }
  name_code = find_ctor_dtor_name_code(func_name);
  if (name_code == -1) {
    name_code = find_operator_name_code(func_name);
    iVar5 = (int)name_code;
    if (iVar5 == -1) {
      if (((func_name[0] == '_') && (func_name[1] == '_')) &&
         ((func_name[2] == 'o' && (func_name[3] == 'p')))) {
        uVar3 = format_mangled_type_list((char *)(func_name + 4),2);
        if (uVar3 != 0) {
          return -1;
        }
        if (sig_kind == 0) {
          iVar5 = append_to_work_buffer(s_operator_prefix,1);
          if (iVar5 == -1) {
            return -1;
          }
          iVar5 = append_to_work_buffer(g_work_buffer_b,1);
          if (iVar5 == -1) {
            return -1;
          }
        }
        else {
          iVar5 = append_to_work_buffer(&g_demangle_class_scope,1);
          if (iVar5 == -1) {
            return -1;
          }
          iVar5 = append_to_work_buffer(s_operator_prefix,1);
          if (iVar5 == -1) {
            return -1;
          }
          iVar5 = append_to_work_buffer(g_work_buffer_b,1);
          if (iVar5 == -1) {
            return -1;
          }
        }
      }
      else if (sig_kind == 0) {
        if ((func_name[0] == '_') &&
           (iVar5 = append_to_work_buffer((char *)(func_name + 1),1), iVar5 == -1)) {
          return -1;
        }
      }
      else {
        iVar5 = append_to_work_buffer(&g_demangle_class_scope,1);
        if (iVar5 == -1) {
          return -1;
        }
        if ((func_name[0] == '_') &&
           (iVar5 = append_to_work_buffer((char *)(func_name + 1),1), iVar5 == -1)) {
          return -1;
        }
      }
    }
    else if (sig_kind == 0) {
      iVar5 = append_to_work_buffer((&PTR_s_operator___00442a5c)[iVar5 * 2],1);
      if (iVar5 == -1) {
        return -1;
      }
    }
    else {
      iVar7 = append_to_work_buffer(&g_demangle_class_scope,1);
      if (iVar7 == -1) {
        return -1;
      }
      iVar5 = append_to_work_buffer((&PTR_s_operator___00442a5c)[iVar5 * 2],1);
      if (iVar5 == -1) {
        return -1;
      }
    }
  }
  else if ((((sig_kind == 1) || (sig_kind == 2)) || (sig_kind == 6)) || (sig_kind == 7)) {
    iVar5 = append_to_work_buffer(&g_demangle_class_scope,1);
    if (iVar5 == -1) {
      return -1;
    }
    iVar5 = append_to_work_buffer((&PTR_s_empty_string_00442bac)[name_code * 2],1);
    if (iVar5 == -1) {
      return -1;
    }
    iVar5 = append_to_work_buffer(class_name,1);
    if (iVar5 == -1) {
      return -1;
    }
  }
  else if ((((sig_kind == 0) || (sig_kind == 3)) || ((sig_kind == 4 || (sig_kind == 5)))) &&
          ((func_name[0] == '_' &&
           (iVar5 = append_to_work_buffer((char *)(func_name + 1),1), iVar5 == -1)))) {
    return -1;
  }
  if (((((sig_kind == 0) || (sig_kind == 1)) || (sig_kind == 2)) ||
      ((sig_kind == 5 || (sig_kind == 6)))) || (sig_kind == 7)) {
    uVar3 = demangle_argument_list(mangled + iVar4 + 1,2);
    if (uVar3 != 0) {
      return (-(ushort)(uVar3 == 2) & 3) - 1;
    }
    iVar4 = append_to_work_buffer((char *)&s_open_paren,1);
    if (iVar4 == -1) {
      return -1;
    }
    iVar4 = append_to_work_buffer(g_work_buffer_b,1);
    if (iVar4 == -1) {
      return -1;
    }
    iVar4 = append_to_work_buffer((char *)&s_close_paren,1);
    if (iVar4 == -1) {
      return -1;
    }
    if ((((sig_kind == 5) || (sig_kind == 6)) || (sig_kind == 7)) &&
       (iVar4 = append_to_work_buffer((char *)&g_demangle_cv_suffix,1), iVar4 == -1)) {
      return -1;
    }
  }
  *demangled = g_work_buffer_a;
  return 0;
#undef local_408
#undef sig_len
#undef func_name
#undef cv_codes
#undef class_code
#undef class_name
}



