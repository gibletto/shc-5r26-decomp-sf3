#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_demangle_placeholder_chunk_current
#define g_demangle_placeholder_chunk_current (*(int * *)(g_sd + 0x14f64))
#undef g_demangle_placeholder_chunk_first
#define g_demangle_placeholder_chunk_first (*(int * *)(g_sd + 0x14f60))
#undef g_demangle_token_text
#define g_demangle_token_text (*(char *)(g_sd + 0xbcb0))
#undef g_work_buffer_c
#define g_work_buffer_c (*(char * *)(g_sd + 0x14f90))


// entry: 00430320
// name : demangle_argument_list
// size : 2986
// sig  : ushort demangle_argument_list(char * codes, int buffer)


/* WARNING: Removing unreachable block (ram,0x00430dd6) */
/* WARNING: Removing unreachable block (ram,0x00430dd8) */
/* WARNING: Removing unreachable block (ram,0x00430d99) */
/* WARNING: Removing unreachable block (ram,0x00430d9b) */

ushort __cdecl demangle_argument_list(char *codes,int buffer)

{
  unsigned char _frec_1a[26];
#define token_count (*(short *)(_frec_1a + 0))
#define pos (*(int *)(_frec_1a + 2))
#define code_len (*(int *)(_frec_1a + 6))
#define local_10 (*(uint *)(_frec_1a + 10))
#define placeholder_name (*(char (*)[5])(_frec_1a + 14))
#define local_7 (*(undefined1 *)(_frec_1a + 19))
  char cVar1;
  short sVar2;
  undefined4 *puVar3;
  undefined4 *block;
  bool bVar4;
  short sVar5;
  ushort uVar6;
  int iVar7;
  demangle_entry *ent;
  uint uVar8;
  int iVar9;
  uint uVar10;
  short tok;
  char **token_text;
  char *pcVar11;
  char *pcVar12;
  char *pcVar13;
  
  token_count = 0;
  g_demangle_token_pool_used = 0;
  bVar4 = false;
  g_demangle_placeholder_name_pool_used = 0;
  g_demangle_placeholder_count = 0;
  g_demangle_placeholder_chunk_first = (undefined4 *)0x0;
  g_demangle_placeholder_chunk_current = (undefined4 *)0x0;
  g_demangle_placeholder_chunk_used = 0;
  iVar7 = reset_work_buffer(3);
  if (iVar7 == -1) {
    return 0xffff;
  }
  (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = 0;
  ent = g_demangle_tokens;
  do {
    ent->kind = 0;
    ent = ent + 1;
  } while (ent < g_demangle_placeholder_types);
  ent = g_demangle_placeholder_types;
  do {
    ent->kind = 0;
    ent = ent + 1;
  } while (ent < (demangle_entry *)&g_demangle_piece_chunk_first);
  pos = 0;
  cVar1 = *codes;
  do {
    if (cVar1 == '\0') {
      iVar7 = 0;
      g_demangle_joined_tokens = 0;
      if (0 < token_count) {
        token_text = &g_demangle_tokens[0].text;
        do {
          uVar8 = 0xffffffff;
          pcVar11 = *token_text;
          do {
            pcVar13 = pcVar11;
            if (uVar8 == 0) break;
            uVar8 = uVar8 - 1;
            pcVar13 = pcVar11 + 1;
            cVar1 = *pcVar11;
            pcVar11 = pcVar13;
          } while (cVar1 != '\0');
          uVar8 = ~uVar8;
          iVar9 = -1;
          pcVar11 = &g_demangle_joined_tokens;
          do {
            pcVar12 = pcVar11;
            if (iVar9 == 0) break;
            iVar9 = iVar9 + -1;
            pcVar12 = pcVar11 + 1;
            cVar1 = *pcVar11;
            pcVar11 = pcVar12;
          } while (cVar1 != '\0');
          token_text = token_text + 2;
          pcVar11 = pcVar13 + -uVar8;
          pcVar13 = pcVar12 + -1;
          for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
            *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
            pcVar11 = pcVar11 + 4;
            pcVar13 = pcVar13 + 4;
          }
          iVar7 = iVar7 + 1;
          for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
            *pcVar13 = *pcVar11;
            pcVar11 = pcVar11 + 1;
            pcVar13 = pcVar13 + 1;
          }
        } while (iVar7 < token_count);
      }
      uVar6 = format_mangled_type_list(&g_demangle_joined_tokens,buffer);
      block = g_demangle_placeholder_chunk_first;
      while (block != (undefined4 *)0x0) {
        puVar3 = (undefined4 *)*block;
        stock_free(block);
        block = puVar3;
      }
      return uVar6;
    }
    pcVar11 = codes + pos;
    sVar5 = classify_mangle_code(pcVar11);
    switch(sVar5) {
    case 1:
      (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = *pcVar11;
      (*(unsigned char *)((char *)&g_demangle_token_text + 1)) = 0;
      push_demangle_token((char *)&g_demangle_token_text,&token_count);
      pos = pos + 1;
      (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = 0;
      break;
    case 2:
      if (*pcVar11 == 'm') {
        uVar6 = copy_length_prefixed_name
                          (pcVar11 + 1,(char *)((int)&g_demangle_token_text + 1),&code_len);
        if (uVar6 != 0) {
          return 0xffff;
        }
        (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = 0x6d;
        g_demangle_tokens[token_count].kind = 3;
        push_demangle_token((char *)&g_demangle_token_text,&token_count);
        pos = pos + code_len + 1;
      }
      else {
        (*(unsigned char *)((char *)&g_demangle_token_text + 1)) = 0;
        (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = *pcVar11;
        g_demangle_tokens[token_count].kind = 3;
        push_demangle_token((char *)&g_demangle_token_text,&token_count);
        pos = pos + 1;
      }
      (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = 0;
      if (bVar4) {
        if (g_demangle_placeholder_chunk_first == (undefined4 *)0x0) {
          g_demangle_placeholder_chunk_first = stock_malloc(0x804);
          if (g_demangle_placeholder_chunk_first == (undefined4 *)0x0) {
            g_demangle_placeholder_chunk_first = (undefined4 *)0x0;
            return 2;
          }
          g_demangle_placeholder_chunk_current = g_demangle_placeholder_chunk_first;
          *g_demangle_placeholder_chunk_first = 0;
        }
        sVar5 = token_count;
        bVar4 = false;
        if (token_count != 0) {
          do {
            if (g_demangle_tokens[token_count].kind == 1) {
              token_count = token_count + -1;
              goto LAB_004304f7;
            }
            token_count = token_count + -1;
          } while (token_count != 0);
          token_count = 0;
        }
LAB_004304f7:
        if (token_count == 0) {
LAB_0043052c:
          if ((g_demangle_tokens[token_count].kind == 1) ||
             (g_demangle_tokens[token_count].kind == 3)) {
            token_count = token_count + 1;
          }
        }
        else {
          do {
            if ((g_demangle_tokens[token_count].kind == 3) ||
               (g_demangle_tokens[token_count].kind == 1)) {
              token_count = token_count + 1;
              goto LAB_00430525;
            }
            token_count = token_count + -1;
          } while (token_count != 0);
          token_count = 0;
LAB_00430525:
          if (token_count == 0) goto LAB_0043052c;
        }
        sVar2 = g_demangle_tokens[sVar5].kind;
        tok = sVar5;
        while (sVar2 != 2) {
          tok = tok + -1;
          sVar2 = g_demangle_tokens[tok].kind;
        }
        g_demangle_joined_tokens = 0;
        while (tok = tok + 1, tok < sVar5) {
          local_10 = 0xffffffff;
          pcVar11 = g_demangle_tokens[tok].text;
          do {
            pcVar13 = pcVar11;
            if (local_10 == 0) break;
            local_10 = local_10 - 1;
            pcVar13 = pcVar11 + 1;
            cVar1 = *pcVar11;
            pcVar11 = pcVar13;
          } while (cVar1 != '\0');
          local_10 = ~local_10;
          iVar7 = -1;
          pcVar11 = &g_demangle_joined_tokens;
          do {
            pcVar12 = pcVar11;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar12 = pcVar11 + 1;
            cVar1 = *pcVar11;
            pcVar11 = pcVar12;
          } while (cVar1 != '\0');
          pcVar11 = pcVar13 + -local_10;
          pcVar13 = pcVar12 + -1;
          for (uVar8 = local_10 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
            *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
            pcVar11 = pcVar11 + 4;
            pcVar13 = pcVar13 + 4;
          }
          for (uVar8 = local_10 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
            *pcVar13 = *pcVar11;
            pcVar11 = pcVar11 + 1;
            pcVar13 = pcVar13 + 1;
          }
          g_demangle_tokens[tok].kind = 0;
        }
        uVar6 = format_mangled_type_list(&g_demangle_joined_tokens,3);
        if (uVar6 != 0) {
          return 0xffff;
        }
        if (0x400 < g_work_buffer_c_length) {
          return 0xffff;
        }
        uVar8 = 0xffffffff;
        pcVar11 = g_work_buffer_c;
        do {
          pcVar13 = pcVar11;
          if (uVar8 == 0) break;
          uVar8 = uVar8 - 1;
          pcVar13 = pcVar11 + 1;
          cVar1 = *pcVar11;
          pcVar11 = pcVar13;
        } while (cVar1 != '\0');
        uVar8 = ~uVar8;
        pcVar11 = pcVar13 + -uVar8;
        pcVar13 = (char *)&g_demangle_token_text;
        for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
          pcVar11 = pcVar11 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
          *pcVar13 = *pcVar11;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        }
        sVar5 = g_demangle_tokens[token_count].kind;
        g_demangle_joined_tokens = 0;
        iVar7 = 0;
        while (sVar5 != 2) {
          uVar8 = 0xffffffff;
          pcVar11 = g_demangle_tokens[token_count + iVar7].text;
          do {
            pcVar13 = pcVar11;
            if (uVar8 == 0) break;
            uVar8 = uVar8 - 1;
            pcVar13 = pcVar11 + 1;
            cVar1 = *pcVar11;
            pcVar11 = pcVar13;
          } while (cVar1 != '\0');
          uVar8 = ~uVar8;
          iVar9 = -1;
          pcVar11 = &g_demangle_joined_tokens;
          do {
            pcVar12 = pcVar11;
            if (iVar9 == 0) break;
            iVar9 = iVar9 + -1;
            pcVar12 = pcVar11 + 1;
            cVar1 = *pcVar11;
            pcVar11 = pcVar12;
          } while (cVar1 != '\0');
          pcVar11 = pcVar13 + -uVar8;
          pcVar13 = pcVar12 + -1;
          for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
            *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
            pcVar11 = pcVar11 + 4;
            pcVar13 = pcVar13 + 4;
          }
          for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
            *pcVar13 = *pcVar11;
            pcVar11 = pcVar11 + 1;
            pcVar13 = pcVar13 + 1;
          }
          g_demangle_tokens[iVar7 + token_count].kind = 0;
          sVar5 = g_demangle_tokens[(int)token_count + iVar7 + 1].kind;
          iVar7 = iVar7 + 1;
        }
        g_demangle_tokens[token_count + iVar7].kind = 0;
        uVar6 = format_mangled_type_list(&g_demangle_joined_tokens,3);
        if (uVar6 != 0) {
          return 0xffff;
        }
        if (0x400 < g_work_buffer_c_length) {
          return 0xffff;
        }
        uVar8 = 0xffffffff;
        pcVar11 = g_work_buffer_c;
        do {
          pcVar13 = pcVar11;
          if (uVar8 == 0) break;
          uVar8 = uVar8 - 1;
          pcVar13 = pcVar11 + 1;
          cVar1 = *pcVar11;
          pcVar11 = pcVar13;
        } while (cVar1 != '\0');
        uVar8 = ~uVar8;
        iVar7 = -1;
        pcVar11 = (char *)&g_demangle_token_text;
        do {
          pcVar12 = pcVar11;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar12 = pcVar11 + 1;
          cVar1 = *pcVar11;
          pcVar11 = pcVar12;
        } while (cVar1 != '\0');
        pcVar11 = pcVar13 + -uVar8;
        pcVar13 = pcVar12 + -1;
        for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
          pcVar11 = pcVar11 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
          *pcVar13 = *pcVar11;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        }
        uVar8 = 0xffffffff;
        pcVar11 = (char *)&s_close_paren;
        do {
          pcVar13 = pcVar11;
          if (uVar8 == 0) break;
          uVar8 = uVar8 - 1;
          pcVar13 = pcVar11 + 1;
          cVar1 = *pcVar11;
          pcVar11 = pcVar13;
        } while (cVar1 != '\0');
        uVar8 = ~uVar8;
        iVar7 = -1;
        pcVar11 = (char *)&g_demangle_token_text;
        do {
          pcVar12 = pcVar11;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar12 = pcVar11 + 1;
          cVar1 = *pcVar11;
          pcVar11 = pcVar12;
        } while (cVar1 != '\0');
        pcVar11 = pcVar13 + -uVar8;
        pcVar13 = pcVar12 + -1;
        for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
          pcVar11 = pcVar11 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
          *pcVar13 = *pcVar11;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        }
        pcVar11 = alloc_placeholder_type_string((char *)&g_demangle_token_text);
        iVar7 = g_demangle_placeholder_count;
        g_demangle_placeholder_types[g_demangle_placeholder_count].text = pcVar11;
        if (g_demangle_placeholder_types[iVar7].text == (char *)0x0) {
          return 2;
        }
        g_demangle_placeholder_types[iVar7].kind = 1;
        _sprintf(placeholder_name,s_placeholder_name_format,iVar7);
        local_7 = 0;
        iVar7 = intern_placeholder_name(placeholder_name);
        iVar9 = (int)token_count;
        token_count = token_count + 1;
        g_demangle_placeholder_count = g_demangle_placeholder_count + 1;
        g_demangle_tokens[iVar9].text = &g_demangle_placeholder_name_pool + iVar7;
        g_demangle_tokens[iVar9].kind = 3;
      }
      break;
    case 3:
      (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = *pcVar11;
      (*(unsigned char *)((char *)&g_demangle_token_text + 1)) = 0;
      push_demangle_token((char *)&g_demangle_token_text,&token_count);
      pos = pos + 1;
      (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = 0;
      break;
    case 4:
      (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = *pcVar11;
      (*(unsigned char *)((char *)&g_demangle_token_text + 1)) = 0;
      g_demangle_tokens[token_count].kind = 1;
      push_demangle_token((char *)&g_demangle_token_text,&token_count);
      pos = pos + 1;
      (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = 0;
      break;
    case 5:
    case 0xb:
      if (sVar5 == 5) {
        uVar6 = copy_length_prefixed_name(pcVar11,(char *)&g_demangle_token_text,&code_len);
      }
      else {
        uVar6 = copy_qualified_name_code(pcVar11,(char *)&g_demangle_token_text,&code_len);
      }
      if (uVar6 != 0) {
        return 0xffff;
      }
      g_demangle_tokens[token_count].kind = 3;
      push_demangle_token((char *)&g_demangle_token_text,&token_count);
      (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = 0;
      pos = pos + code_len;
      if (bVar4) {
        if (g_demangle_placeholder_chunk_first == (undefined4 *)0x0) {
          g_demangle_placeholder_chunk_first = stock_malloc(0x804);
          if (g_demangle_placeholder_chunk_first == (undefined4 *)0x0) {
            g_demangle_placeholder_chunk_first = (undefined4 *)0x0;
            return 2;
          }
          g_demangle_placeholder_chunk_current = g_demangle_placeholder_chunk_first;
          *g_demangle_placeholder_chunk_first = 0;
        }
        sVar5 = token_count;
        bVar4 = false;
        if (token_count != 0) {
          do {
            if (g_demangle_tokens[token_count].kind == 1) {
              token_count = token_count + -1;
              goto LAB_004308eb;
            }
            token_count = token_count + -1;
          } while (token_count != 0);
          token_count = 0;
        }
LAB_004308eb:
        if (token_count == 0) {
LAB_00430920:
          if ((g_demangle_tokens[token_count].kind == 1) ||
             (g_demangle_tokens[token_count].kind == 3)) {
            token_count = token_count + 1;
          }
        }
        else {
          do {
            if ((g_demangle_tokens[token_count].kind == 3) ||
               (g_demangle_tokens[token_count].kind == 1)) {
              token_count = token_count + 1;
              goto LAB_00430919;
            }
            token_count = token_count + -1;
          } while (token_count != 0);
          token_count = 0;
LAB_00430919:
          if (token_count == 0) goto LAB_00430920;
        }
        sVar2 = g_demangle_tokens[sVar5].kind;
        tok = sVar5;
        while (sVar2 != 2) {
          tok = tok + -1;
          sVar2 = g_demangle_tokens[tok].kind;
        }
        g_demangle_joined_tokens = 0;
        while (tok = tok + 1, tok < sVar5) {
          local_10 = 0xffffffff;
          pcVar11 = g_demangle_tokens[tok].text;
          do {
            pcVar13 = pcVar11;
            if (local_10 == 0) break;
            local_10 = local_10 - 1;
            pcVar13 = pcVar11 + 1;
            cVar1 = *pcVar11;
            pcVar11 = pcVar13;
          } while (cVar1 != '\0');
          local_10 = ~local_10;
          iVar7 = -1;
          pcVar11 = &g_demangle_joined_tokens;
          do {
            pcVar12 = pcVar11;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            pcVar12 = pcVar11 + 1;
            cVar1 = *pcVar11;
            pcVar11 = pcVar12;
          } while (cVar1 != '\0');
          pcVar11 = pcVar13 + -local_10;
          pcVar13 = pcVar12 + -1;
          for (uVar8 = local_10 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
            *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
            pcVar11 = pcVar11 + 4;
            pcVar13 = pcVar13 + 4;
          }
          for (uVar8 = local_10 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
            *pcVar13 = *pcVar11;
            pcVar11 = pcVar11 + 1;
            pcVar13 = pcVar13 + 1;
          }
          g_demangle_tokens[tok].kind = 0;
        }
        uVar6 = format_mangled_type_list(&g_demangle_joined_tokens,3);
        if (uVar6 != 0) {
          return 0xffff;
        }
        if (0x400 < g_work_buffer_c_length) {
          return 0xffff;
        }
        uVar8 = 0xffffffff;
        pcVar11 = g_work_buffer_c;
        do {
          pcVar13 = pcVar11;
          if (uVar8 == 0) break;
          uVar8 = uVar8 - 1;
          pcVar13 = pcVar11 + 1;
          cVar1 = *pcVar11;
          pcVar11 = pcVar13;
        } while (cVar1 != '\0');
        uVar8 = ~uVar8;
        pcVar11 = pcVar13 + -uVar8;
        pcVar13 = (char *)&g_demangle_token_text;
        for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
          pcVar11 = pcVar11 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
          *pcVar13 = *pcVar11;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        }
        sVar5 = g_demangle_tokens[token_count].kind;
        g_demangle_joined_tokens = 0;
        iVar7 = 0;
        while (sVar5 != 2) {
          uVar8 = 0xffffffff;
          pcVar11 = g_demangle_tokens[token_count + iVar7].text;
          do {
            pcVar13 = pcVar11;
            if (uVar8 == 0) break;
            uVar8 = uVar8 - 1;
            pcVar13 = pcVar11 + 1;
            cVar1 = *pcVar11;
            pcVar11 = pcVar13;
          } while (cVar1 != '\0');
          uVar8 = ~uVar8;
          iVar9 = -1;
          pcVar11 = &g_demangle_joined_tokens;
          do {
            pcVar12 = pcVar11;
            if (iVar9 == 0) break;
            iVar9 = iVar9 + -1;
            pcVar12 = pcVar11 + 1;
            cVar1 = *pcVar11;
            pcVar11 = pcVar12;
          } while (cVar1 != '\0');
          pcVar11 = pcVar13 + -uVar8;
          pcVar13 = pcVar12 + -1;
          for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
            *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
            pcVar11 = pcVar11 + 4;
            pcVar13 = pcVar13 + 4;
          }
          for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
            *pcVar13 = *pcVar11;
            pcVar11 = pcVar11 + 1;
            pcVar13 = pcVar13 + 1;
          }
          g_demangle_tokens[iVar7 + token_count].kind = 0;
          sVar5 = g_demangle_tokens[(int)token_count + iVar7 + 1].kind;
          iVar7 = iVar7 + 1;
        }
        g_demangle_tokens[token_count + iVar7].kind = 0;
        uVar6 = format_mangled_type_list(&g_demangle_joined_tokens,3);
        if (uVar6 != 0) {
          return 0xffff;
        }
        if (0x400 < g_work_buffer_c_length) {
          return 0xffff;
        }
        uVar8 = 0xffffffff;
        pcVar11 = g_work_buffer_c;
        do {
          pcVar13 = pcVar11;
          if (uVar8 == 0) break;
          uVar8 = uVar8 - 1;
          pcVar13 = pcVar11 + 1;
          cVar1 = *pcVar11;
          pcVar11 = pcVar13;
        } while (cVar1 != '\0');
        uVar8 = ~uVar8;
        iVar7 = -1;
        pcVar11 = (char *)&g_demangle_token_text;
        do {
          pcVar12 = pcVar11;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar12 = pcVar11 + 1;
          cVar1 = *pcVar11;
          pcVar11 = pcVar12;
        } while (cVar1 != '\0');
        pcVar11 = pcVar13 + -uVar8;
        pcVar13 = pcVar12 + -1;
        for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
          pcVar11 = pcVar11 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
          *pcVar13 = *pcVar11;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        }
        uVar8 = 0xffffffff;
        pcVar11 = (char *)&s_close_paren;
        do {
          pcVar13 = pcVar11;
          if (uVar8 == 0) break;
          uVar8 = uVar8 - 1;
          pcVar13 = pcVar11 + 1;
          cVar1 = *pcVar11;
          pcVar11 = pcVar13;
        } while (cVar1 != '\0');
        uVar8 = ~uVar8;
        iVar7 = -1;
        pcVar11 = (char *)&g_demangle_token_text;
        do {
          pcVar12 = pcVar11;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          pcVar12 = pcVar11 + 1;
          cVar1 = *pcVar11;
          pcVar11 = pcVar12;
        } while (cVar1 != '\0');
        pcVar11 = pcVar13 + -uVar8;
        pcVar13 = pcVar12 + -1;
        for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
          pcVar11 = pcVar11 + 4;
          pcVar13 = pcVar13 + 4;
        }
        for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
          *pcVar13 = *pcVar11;
          pcVar11 = pcVar11 + 1;
          pcVar13 = pcVar13 + 1;
        }
        pcVar11 = alloc_placeholder_type_string((char *)&g_demangle_token_text);
        iVar7 = g_demangle_placeholder_count;
        g_demangle_placeholder_types[g_demangle_placeholder_count].text = pcVar11;
        if (g_demangle_placeholder_types[iVar7].text == (char *)0x0) {
          return 2;
        }
        g_demangle_placeholder_types[iVar7].kind = 1;
        _sprintf(placeholder_name,s_placeholder_name_format,iVar7);
        local_7 = 0;
        iVar7 = intern_placeholder_name(placeholder_name);
        iVar9 = (int)token_count;
        token_count = token_count + 1;
        g_demangle_placeholder_count = g_demangle_placeholder_count + 1;
        g_demangle_tokens[iVar9].text = &g_demangle_placeholder_name_pool + iVar7;
        g_demangle_tokens[iVar9].kind = 3;
      }
      break;
    case 6:
      sVar5 = copy_array_dimension_codes(pcVar11,(char *)&g_demangle_token_text,&code_len);
      if (sVar5 != 0) {
        return 0xffff;
      }
      push_demangle_token((char *)&g_demangle_token_text,&token_count);
      (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = 0;
      pos = pos + code_len;
      break;
    case 7:
      sVar5 = copy_member_pointer_code(pcVar11,(char *)&g_demangle_token_text,&code_len);
      if (sVar5 != 0) {
        return 0xffff;
      }
      push_demangle_token((char *)&g_demangle_token_text,&token_count);
      (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = 0;
      pos = pos + code_len;
      break;
    case 8:
      sVar5 = copy_type_back_reference_code(pcVar11,(char *)&g_demangle_token_text,&code_len);
      if (sVar5 != 0) {
        return 0xffff;
      }
      g_demangle_tokens[token_count].kind = 3;
      push_demangle_token((char *)&g_demangle_token_text,&token_count);
      (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = 0;
      pos = pos + code_len;
      break;
    case 9:
      iVar7 = 0;
      do {
        iVar9 = iVar7 + 1;
        *(char *)((int)&g_demangle_token_text + iVar7) = codes[iVar7];
        iVar7 = iVar9;
      } while (iVar9 < 5);
      push_demangle_token((char *)&g_demangle_token_text,&token_count);
      pos = pos + iVar9;
      (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = 0;
      break;
    case 10:
      (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = *pcVar11;
      (*(unsigned char *)((char *)&g_demangle_token_text + 1)) = 0;
      g_demangle_tokens[token_count].kind = 2;
      push_demangle_token((char *)&g_demangle_token_text,&token_count);
      pos = pos + 1;
      (*(unsigned char *)((char *)&g_demangle_token_text + 0)) = 0;
      bVar4 = true;
      break;
    default:
      return 0xffff;
    }
    cVar1 = codes[pos];
  } while( true );
#undef token_count
#undef pos
#undef code_len
#undef local_10
#undef placeholder_name
#undef local_7
}



