#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_demangle_array_type_text
#define g_demangle_array_type_text (*(unsigned char *)(g_sd + 0x98b0))
#undef g_demangle_type_text
#define g_demangle_type_text (*(unsigned char *)(g_sd + 0xa0b0))


// entry: 004315a0
// name : format_mangled_type_list
// size : 2997
// sig  : ushort format_mangled_type_list(char * codes, int buffer)


ushort __cdecl format_mangled_type_list(char *codes,int buffer)

{
  unsigned char _frec_c[12];
#define piece_count (*(short *)(_frec_c + 0))
#define status (*(ushort *)(_frec_c + 2))
#define code_len (*(int *)(_frec_c + 4))
#define next_code (*(char * *)(_frec_c + 8))
  char cVar1;
  short table_index;
  ushort uVar2;
  demangle_entry *ent;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int pos;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  
  piece_count = 0;
  g_demangle_back_reference_count = 0;
  g_demangle_type_piece[0] = '\0';
  (*(unsigned char *)((char *)&g_demangle_type_text + 0)) = 0;
  g_demangle_piece_chunk_first = 0;
  g_demangle_piece_chunk_current = 0;
  g_demangle_backref_chunk_first = 0;
  g_demangle_backref_chunk_current = 0;
  clear_work_buffer(buffer);
  ent = g_demangle_type_pieces;
  do {
    ent->kind = 0;
    ent = ent + 1;
  } while (ent < &g_demangle_back_reference_count);
  ent = g_demangle_back_references;
  do {
    ent->kind = 0;
    ent = ent + 1;
  } while (ent < &g_demangle_placeholder_count);
  pos = 0;
  allocate_demangle_string_chunks();
  do {
    pcVar6 = codes + pos;
    if (*pcVar6 == '\0') {
      free_demangle_string_chunks();
      return 0;
    }
    table_index = classify_mangle_code(pcVar6);
    switch(table_index) {
    case 1:
      table_index = find_type_qualifier_code(pcVar6);
      if (table_index == -1) {
        return status;
      }
      uVar4 = 0xffffffff;
      pcVar7 = (&PTR_s_unsigned_004429cc)[table_index * 2];
      do {
        pcVar9 = pcVar7;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar9 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar9;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar3 = -1;
      pcVar7 = g_demangle_type_piece;
      do {
        pcVar8 = pcVar7;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar8 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar8;
      } while (cVar1 != '\0');
      pcVar7 = pcVar9 + -uVar4;
      pcVar9 = pcVar8 + -1;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar9 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar9 = pcVar9 + 1;
      }
      next_code = pcVar6 + 1;
      table_index = classify_mangle_code(next_code);
      switch(table_index) {
      case 1:
        uVar4 = 0xffffffff;
        pcVar6 = (char *)&s_space;
        do {
          pcVar7 = pcVar6;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar7 = pcVar6 + 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar7;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        iVar3 = -1;
        pcVar6 = g_demangle_type_piece;
        do {
          pcVar9 = pcVar6;
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          pcVar9 = pcVar6 + 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar9;
        } while (cVar1 != '\0');
        pos = pos + 1;
        pcVar6 = pcVar7 + -uVar4;
        pcVar7 = pcVar9 + -1;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar7 = pcVar7 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar7 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar7 = pcVar7 + 1;
        }
        break;
      case 2:
        uVar4 = 0xffffffff;
        pcVar7 = (char *)&s_space;
        do {
          pcVar9 = pcVar7;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar9 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar9;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        iVar3 = -1;
        pcVar7 = g_demangle_type_piece;
        do {
          pcVar8 = pcVar7;
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          pcVar8 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar8;
        } while (cVar1 != '\0');
        pcVar7 = pcVar9 + -uVar4;
        pcVar9 = pcVar8 + -1;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar9 = pcVar9 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar9 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          pcVar9 = pcVar9 + 1;
        }
        if (*next_code == 'm') {
          uVar2 = parse_length_prefixed_name(pcVar6 + 2,(char *)&g_demangle_type_text,&code_len);
          if (uVar2 != 0) {
            return uVar2;
          }
          uVar4 = 0xffffffff;
          pcVar6 = s_enum_prefix;
          do {
            pcVar7 = pcVar6;
            if (uVar4 == 0) break;
            uVar4 = uVar4 - 1;
            pcVar7 = pcVar6 + 1;
            cVar1 = *pcVar6;
            pcVar6 = pcVar7;
          } while (cVar1 != '\0');
          uVar4 = ~uVar4;
          iVar3 = -1;
          pcVar6 = g_demangle_type_piece;
          do {
            pcVar9 = pcVar6;
            if (iVar3 == 0) break;
            iVar3 = iVar3 + -1;
            pcVar9 = pcVar6 + 1;
            cVar1 = *pcVar6;
            pcVar6 = pcVar9;
          } while (cVar1 != '\0');
          pcVar6 = pcVar7 + -uVar4;
          pcVar7 = pcVar9 + -1;
          for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
            pcVar6 = pcVar6 + 4;
            pcVar7 = pcVar7 + 4;
          }
          for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
            *pcVar7 = *pcVar6;
            pcVar6 = pcVar6 + 1;
            pcVar7 = pcVar7 + 1;
          }
          pcVar6 = (char *)&g_demangle_type_text;
          status = 0;
        }
        else {
          table_index = find_basic_type_code(next_code);
          if (table_index == -1) {
            return status;
          }
          pcVar6 = (&PTR_DAT_004429ec)[table_index * 2];
        }
        uVar4 = 0xffffffff;
        do {
          pcVar7 = pcVar6;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar7 = pcVar6 + 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar7;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        iVar3 = -1;
        pcVar6 = g_demangle_type_piece;
        do {
          pcVar9 = pcVar6;
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          pcVar9 = pcVar6 + 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar9;
        } while (cVar1 != '\0');
        pcVar6 = pcVar7 + -uVar4;
        pcVar7 = pcVar9 + -1;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar7 = pcVar7 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar7 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar7 = pcVar7 + 1;
        }
        g_demangle_type_pieces[piece_count].kind = 2;
        push_type_piece(g_demangle_type_piece,&piece_count);
        g_demangle_type_piece[0] = '\0';
        if (*next_code == 'm') {
          pos = pos + code_len + 2;
        }
        else {
          pos = pos + 2;
        }
        (*(unsigned char *)((char *)&g_demangle_type_text + 0)) = 0;
        compose_type_pieces(&piece_count,(char *)&g_demangle_type_text);
        iVar3 = append_to_work_buffer((char *)&g_demangle_type_text,buffer);
        if (iVar3 == -1) {
          return 0xffff;
        }
        remember_argument_type((char *)&g_demangle_type_text);
        (*(unsigned char *)((char *)&g_demangle_type_text + 0)) = 0;
        if ((codes[pos] != '\0') &&
           (iVar3 = append_to_work_buffer(&s_argument_separator,buffer), iVar3 == -1)) {
          return 0xffff;
        }
        break;
      case 3:
      case 7:
        pos = pos + 1;
        push_type_piece(g_demangle_type_piece,&piece_count);
        g_demangle_type_piece[0] = '\0';
        break;
      default:
        return 0xffff;
      case 5:
      case 0xb:
        uVar4 = 0xffffffff;
        pcVar6 = (char *)&s_space;
        do {
          pcVar7 = pcVar6;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar7 = pcVar6 + 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar7;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        iVar3 = -1;
        pcVar6 = g_demangle_type_piece;
        do {
          pcVar9 = pcVar6;
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          pcVar9 = pcVar6 + 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar9;
        } while (cVar1 != '\0');
        pcVar6 = pcVar7 + -uVar4;
        pcVar7 = pcVar9 + -1;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar7 = pcVar7 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar7 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar7 = pcVar7 + 1;
        }
        if (table_index == 5) {
          status = parse_length_prefixed_name(next_code,(char *)&g_demangle_type_text,&code_len);
        }
        else {
          status = format_qualified_name(next_code,(char *)&g_demangle_type_text,&code_len);
        }
        if (status != 0) {
          return status;
        }
        uVar4 = 0xffffffff;
        pcVar6 = (char *)&g_demangle_type_text;
        do {
          pcVar7 = pcVar6;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar7 = pcVar6 + 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar7;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        iVar3 = -1;
        pcVar6 = g_demangle_type_piece;
        do {
          pcVar9 = pcVar6;
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          pcVar9 = pcVar6 + 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar9;
        } while (cVar1 != '\0');
        pcVar6 = pcVar7 + -uVar4;
        pcVar7 = pcVar9 + -1;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar7 = pcVar7 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar7 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar7 = pcVar7 + 1;
        }
        g_demangle_type_pieces[piece_count].kind = 2;
        push_type_piece(g_demangle_type_piece,&piece_count);
        g_demangle_type_piece[0] = '\0';
        pos = pos + code_len + 1;
        (*(unsigned char *)((char *)&g_demangle_type_text + 0)) = 0;
        compose_type_pieces(&piece_count,(char *)&g_demangle_type_text);
        iVar3 = append_to_work_buffer((char *)&g_demangle_type_text,buffer);
        if (iVar3 == -1) {
          return 0xffff;
        }
        remember_argument_type((char *)&g_demangle_type_text);
        (*(unsigned char *)((char *)&g_demangle_type_text + 0)) = 0;
        if ((codes[pos] != '\0') &&
           (iVar3 = append_to_work_buffer(&s_argument_separator,buffer), iVar3 == -1)) {
          return 0xffff;
        }
      }
      break;
    case 2:
      if (*pcVar6 == 'm') {
        uVar4 = 0xffffffff;
        pcVar7 = s_enum_prefix;
        do {
          pcVar9 = pcVar7;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar9 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar9;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        iVar3 = -1;
        pcVar7 = g_demangle_type_piece;
        do {
          pcVar8 = pcVar7;
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          pcVar8 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar8;
        } while (cVar1 != '\0');
        pcVar7 = pcVar9 + -uVar4;
        pcVar9 = pcVar8 + -1;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar9 = pcVar9 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar9 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          pcVar9 = pcVar9 + 1;
        }
        status = parse_length_prefixed_name(pcVar6 + 1,g_demangle_type_piece + 5,&code_len);
        if (status != 0) {
          return status;
        }
      }
      else {
        table_index = find_basic_type_code(pcVar6);
        if (table_index == -1) {
          return status;
        }
        uVar4 = 0xffffffff;
        pcVar7 = (&PTR_DAT_004429ec)[table_index * 2];
        do {
          pcVar9 = pcVar7;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar9 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar9;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        iVar3 = -1;
        pcVar7 = g_demangle_type_piece;
        do {
          pcVar8 = pcVar7;
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          pcVar8 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar8;
        } while (cVar1 != '\0');
        pcVar7 = pcVar9 + -uVar4;
        pcVar9 = pcVar8 + -1;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar9 = pcVar9 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar9 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          pcVar9 = pcVar9 + 1;
        }
      }
      g_demangle_type_pieces[piece_count].kind = 2;
      push_type_piece(g_demangle_type_piece,&piece_count);
      g_demangle_type_piece[0] = '\0';
      if (*pcVar6 == 'm') {
        pos = pos + code_len + 1;
      }
      else {
        pos = pos + 1;
      }
      (*(unsigned char *)((char *)&g_demangle_type_text + 0)) = 0;
      compose_type_pieces(&piece_count,(char *)&g_demangle_type_text);
      iVar3 = append_to_work_buffer((char *)&g_demangle_type_text,buffer);
      if (iVar3 == -1) {
        return 0xffff;
      }
      remember_argument_type((char *)&g_demangle_type_text);
      (*(unsigned char *)((char *)&g_demangle_type_text + 0)) = 0;
      if ((codes[pos] != '\0') &&
         (iVar3 = append_to_work_buffer(&s_argument_separator,buffer), iVar3 == -1)) {
        return 0xffff;
      }
      break;
    case 3:
      table_index = find_declarator_code(pcVar6);
      if (table_index == -1) {
        return status;
      }
      uVar4 = 0xffffffff;
      pcVar6 = (&PTR_DAT_00442a3c)[table_index * 2];
      do {
        pcVar7 = pcVar6;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar7 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar7;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar3 = -1;
      pcVar6 = g_demangle_type_piece;
      do {
        pcVar9 = pcVar6;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar9 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar9;
      } while (cVar1 != '\0');
      pos = pos + 1;
      pcVar6 = pcVar7 + -uVar4;
      pcVar7 = pcVar9 + -1;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar7 = pcVar7 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar7 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar7 = pcVar7 + 1;
      }
      push_type_piece(g_demangle_type_piece,&piece_count);
      g_demangle_type_piece[0] = '\0';
      break;
    case 4:
      iVar3 = append_to_work_buffer((char *)&s_open_paren,buffer);
      if (iVar3 == -1) {
        return 0xffff;
      }
      table_index = find_declarator_code(pcVar6);
      if (table_index == -1) {
        return status;
      }
      uVar4 = 0xffffffff;
      pcVar6 = (&PTR_DAT_00442a3c)[table_index * 2];
      do {
        pcVar7 = pcVar6;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar7 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar7;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar3 = -1;
      pcVar6 = g_demangle_type_piece;
      do {
        pcVar9 = pcVar6;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar9 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar9;
      } while (cVar1 != '\0');
      pcVar6 = pcVar7 + -uVar4;
      pcVar7 = pcVar9 + -1;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar7 = pcVar7 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar7 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar7 = pcVar7 + 1;
      }
      if (piece_count == 0) {
        return 0xffff;
      }
      (*(unsigned char *)((char *)&g_demangle_type_text + 0)) = 0;
      compose_type_pieces(&piece_count,(char *)&g_demangle_type_text);
      iVar3 = append_to_work_buffer((char *)&g_demangle_type_text,buffer);
      if (iVar3 == -1) {
        return 0xffff;
      }
      (*(unsigned char *)((char *)&g_demangle_type_text + 0)) = 0;
      iVar3 = append_to_work_buffer(g_demangle_type_piece,buffer);
      if (iVar3 == -1) {
        return 0xffff;
      }
      g_demangle_type_piece[0] = '\0';
      pos = pos + 1;
      break;
    case 5:
    case 0xb:
      if (table_index == 5) {
        status = parse_length_prefixed_name(pcVar6,g_demangle_type_piece,&code_len);
      }
      else {
        status = format_qualified_name(pcVar6,g_demangle_type_piece,&code_len);
      }
      if (status != 0) {
        return status;
      }
      g_demangle_type_pieces[piece_count].kind = 2;
      push_type_piece(g_demangle_type_piece,&piece_count);
      pos = pos + code_len;
      g_demangle_type_piece[0] = '\0';
      (*(unsigned char *)((char *)&g_demangle_type_text + 0)) = 0;
      compose_type_pieces(&piece_count,(char *)&g_demangle_type_text);
      iVar3 = append_to_work_buffer((char *)&g_demangle_type_text,buffer);
      if (iVar3 == -1) {
        return 0xffff;
      }
      remember_argument_type((char *)&g_demangle_type_text);
      (*(unsigned char *)((char *)&g_demangle_type_text + 0)) = 0;
      if ((codes[pos] != '\0') &&
         (iVar3 = append_to_work_buffer(&s_argument_separator,buffer), iVar3 == -1)) {
        return 0xffff;
      }
      break;
    case 6:
      status = format_array_dimensions(pcVar6,g_demangle_type_piece,&code_len);
      if (status != 0) {
        return status;
      }
      if (piece_count == 0) {
        pcVar6 = g_demangle_type_piece;
      }
      else {
        uVar4 = 0xffffffff;
        pcVar6 = (char *)&s_open_paren;
        do {
          pcVar7 = pcVar6;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar7 = pcVar6 + 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar7;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        pcVar6 = pcVar7 + -uVar4;
        pcVar7 = (char *)&g_demangle_array_type_text;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar7 = pcVar7 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar7 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar7 = pcVar7 + 1;
        }
        compose_type_pieces(&piece_count,(char *)&g_demangle_array_type_text);
        uVar4 = 0xffffffff;
        pcVar6 = (char *)&s_close_paren;
        do {
          pcVar7 = pcVar6;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar7 = pcVar6 + 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar7;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        iVar3 = -1;
        pcVar6 = (char *)&g_demangle_array_type_text;
        do {
          pcVar9 = pcVar6;
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          pcVar9 = pcVar6 + 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar9;
        } while (cVar1 != '\0');
        pcVar6 = pcVar7 + -uVar4;
        pcVar7 = pcVar9 + -1;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar7 = pcVar7 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar7 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar7 = pcVar7 + 1;
        }
        push_type_piece(g_demangle_type_piece,&piece_count);
        pcVar6 = (char *)&g_demangle_array_type_text;
      }
      push_type_piece(pcVar6,&piece_count);
      pos = pos + code_len;
      g_demangle_type_piece[0] = '\0';
      (*(unsigned char *)((char *)&g_demangle_array_type_text + 0)) = 0;
      break;
    case 7:
      status = format_member_pointer_class(pcVar6,g_demangle_type_piece,&code_len);
      if (status != 0) {
        return status;
      }
      g_demangle_type_pieces[piece_count].kind = 7;
      push_type_piece(g_demangle_type_piece,&piece_count);
      pos = pos + code_len;
      g_demangle_type_piece[0] = '\0';
      break;
    case 8:
      status = format_type_back_reference(pcVar6,g_demangle_type_piece,&code_len);
      if (status != 0) {
        return status;
      }
      push_type_piece(g_demangle_type_piece,&piece_count);
      pos = pos + code_len;
      g_demangle_type_piece[0] = '\0';
      (*(unsigned char *)((char *)&g_demangle_type_text + 0)) = 0;
      compose_type_pieces(&piece_count,(char *)&g_demangle_type_text);
      iVar3 = append_to_work_buffer((char *)&g_demangle_type_text,buffer);
      if (iVar3 == -1) {
        return 0xffff;
      }
      (*(unsigned char *)((char *)&g_demangle_type_text + 0)) = 0;
      if ((codes[pos] != '\0') &&
         (iVar3 = append_to_work_buffer(&s_argument_separator,buffer), iVar3 == -1)) {
        return 0xffff;
      }
      break;
    case 9:
      status = format_placeholder_type(pcVar6,g_demangle_type_piece,&code_len);
      if (status != 0) {
        return status;
      }
      push_type_piece(g_demangle_type_piece,&piece_count);
      pos = pos + code_len;
      g_demangle_type_piece[0] = '\0';
      (*(unsigned char *)((char *)&g_demangle_type_text + 0)) = 0;
      compose_type_pieces(&piece_count,(char *)&g_demangle_type_text);
      iVar3 = append_to_work_buffer((char *)&g_demangle_type_text,buffer);
      if (iVar3 == -1) {
        return 0xffff;
      }
      remember_argument_type((char *)&g_demangle_type_text);
      (*(unsigned char *)((char *)&g_demangle_type_text + 0)) = 0;
      if ((codes[pos] != '\0') &&
         (iVar3 = append_to_work_buffer(&s_argument_separator,buffer), iVar3 == -1)) {
        return 0xffff;
      }
      break;
    default:
      return 0xffff;
    }
  } while( true );
#undef piece_count
#undef status
#undef code_len
#undef next_code
}



