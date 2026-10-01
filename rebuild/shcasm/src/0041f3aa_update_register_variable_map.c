#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_expno_register_variables
#define g_expno_register_variables (*(register_variable ** *)(g_sd + 0x13008))
#undef g_expno_use_list
#define g_expno_use_list (*(expno_use * *)(g_sd + 0x10c80))
#undef g_new_register_variable_map
#define g_new_register_variable_map (*(register_variable * *)(g_sd + 0x9318))
#undef g_register_candidates
#define g_register_candidates (*(register_candidate * *)(g_sd + 0xf8f8))
#undef g_register_map_temp
#define g_register_map_temp (*(FILE * *)(g_sd + 0x13020))
#undef g_register_variable_map
#define g_register_variable_map (*(register_variable * *)(g_sd + 0x931c))


// entry: 0041f3aa
// name : update_register_variable_map
// size : 1250
// sig  : int update_register_variable_map(void)


int __cdecl update_register_variable_map(void)

{
  unsigned char _frec_3c[60];
#define cand (*(register_candidate * *)(_frec_3c + 0))
#define merged (*(int *)(_frec_3c + 4))
#define use_node (*(expno_use * *)(_frec_3c + 12))
#define alt_walk (*(register_candidate * *)(_frec_3c + 16))
#define match_cand (*(register_candidate * *)(_frec_3c + 20))
#define out_buf (*(char *)(_frec_3c + 24))
#define local_23 (*(undefined1 *)(_frec_3c + 25))
#define local_22 (*(undefined1 *)(_frec_3c + 26))
#define local_21 (*(undefined1 *)(_frec_3c + 27))
#define best_cand (*(register_candidate * *)(_frec_3c + 28))
#define map_node (*(register_variable * *)(_frec_3c + 32))
#define next_alt (*(register_candidate * *)(_frec_3c + 36))
#define local_14 (*(register_variable * *)(_frec_3c + 40))
#define alt_node (*(register_candidate * *)(_frec_3c + 44))
#define local_c (*(undefined2 *)(_frec_3c + 48))
#define var_node (*(register_variable * *)(_frec_3c + 52))
  register_candidate *prVar1;
  register_candidate *new_cand;
  uint nwritten;
  expno_use *next_use;
  
  merged = 0;
  use_node = g_expno_use_list;
  while (use_node != (expno_use *)0x0) {
    next_use = use_node->next;
    for (var_node = g_expno_register_variables[use_node->expno];
        var_node != (register_variable *)0x0; var_node = var_node->next) {
      for (match_cand = g_register_candidates; match_cand != (register_candidate *)0x0;
          match_cand = match_cand->next) {
        if (match_cand->reg == var_node->reg) goto LAB_0041f43d;
      }
      new_cand = pool_alloc(0x10);
      new_cand->reg = var_node->reg;
      new_cand->variable = var_node->variable;
      prVar1 = new_cand;
      match_cand = new_cand;
      if (g_register_candidates != (register_candidate *)0x0) {
        for (match_cand = g_register_candidates; match_cand->next != (register_candidate *)0x0;
            match_cand = match_cand->next) {
        }
        match_cand->next = new_cand;
        prVar1 = g_register_candidates;
        match_cand = new_cand;
      }
LAB_0041f3f6:
      g_register_candidates = prVar1;
      match_cand->weight = use_node->count + match_cand->weight;
    }
    pool_free(use_node,0xc);
    use_node = next_use;
  }
  g_expno_use_list = (expno_use *)0x0;
  cand = g_register_candidates;
  while (cand != (register_candidate *)0x0) {
    prVar1 = cand->next;
    best_cand = cand;
    for (alt_walk = cand; alt_walk != (register_candidate *)0x0; alt_walk = alt_walk->alternative) {
      if (best_cand->weight < alt_walk->weight) {
        best_cand = alt_walk;
      }
    }
    var_node = pool_alloc(8);
    var_node->reg = best_cand->reg;
    var_node->variable = best_cand->variable;
    var_node->next = g_new_register_variable_map;
    alt_node = cand;
    g_new_register_variable_map = var_node;
    while (cand = prVar1, alt_node != (register_candidate *)0x0) {
      next_alt = alt_node->alternative;
      pool_free(alt_node,0x10);
      alt_node = next_alt;
    }
  }
  for (var_node = g_new_register_variable_map; var_node != (register_variable *)0x0;
      var_node = var_node->next) {
    for (local_14 = g_register_variable_map; local_14 != (register_variable *)0x0;
        local_14 = local_14->next) {
      if ((local_14->reg == var_node->reg) && (local_14->variable != var_node->variable))
      goto LAB_0041f6cc;
    }
  }
LAB_0041f6cc:
  if (var_node == (register_variable *)0x0) {
    if (g_register_variable_map == (register_variable *)0x0) {
      g_register_variable_map = g_new_register_variable_map;
    }
    else {
      var_node = g_new_register_variable_map;
      while (var_node != (register_variable *)0x0) {
        local_14 = var_node->next;
        for (map_node = g_register_variable_map;
            (map_node->reg != var_node->reg && (map_node->next != (register_variable *)0x0));
            map_node = map_node->next) {
        }
        if (map_node->next == (register_variable *)0x0) {
          var_node->next = (register_variable *)0x0;
          map_node->next = var_node;
        }
        else {
          pool_free(var_node,8);
        }
        var_node = local_14;
      }
    }
    merged = 1;
  }
  else {
    var_node = g_register_variable_map;
    while (var_node != (register_variable *)0x0) {
      local_14 = var_node->next;
      out_buf = (char)var_node->reg;
      local_23 = *(undefined1 *)((int)&var_node->reg + 1);
      local_22 = (undefined1)var_node->variable;
      local_21 = *(undefined1 *)((int)&var_node->variable + 1);
      nwritten = write_file_bytes(g_register_map_temp,&out_buf,4);
      if (nwritten == 0xffffffff) {
        report_message_at_source_line(0,0,0xce7,(char *)0x0);
      }
      pool_free(var_node,8);
      var_node = local_14;
    }
    local_c = 0xffff;
    out_buf = -1;
    local_23 = 0xff;
    nwritten = write_file_bytes(g_register_map_temp,&out_buf,2);
    if (nwritten == 0xffffffff) {
      report_message_at_source_line(0,0,0xce7,(char *)0x0);
    }
    g_register_variable_map = g_new_register_variable_map;
  }
  g_new_register_variable_map = (register_variable *)0x0;
  g_register_candidates = (register_candidate *)0x0;
  return merged;
LAB_0041f43d:
  prVar1 = g_register_candidates;
  if (match_cand->variable == var_node->variable) goto LAB_0041f3f6;
  if (match_cand->alternative == (register_candidate *)0x0) {
    new_cand = pool_alloc(0x10);
    new_cand->reg = var_node->reg;
    new_cand->variable = var_node->variable;
    match_cand->alternative = new_cand;
    prVar1 = g_register_candidates;
    match_cand = new_cand;
    goto LAB_0041f3f6;
  }
  match_cand = match_cand->alternative;
  goto LAB_0041f43d;
#undef cand
#undef merged
#undef use_node
#undef alt_walk
#undef match_cand
#undef out_buf
#undef local_23
#undef local_22
#undef local_21
#undef best_cand
#undef map_node
#undef next_alt
#undef local_14
#undef alt_node
#undef local_c
#undef var_node
}



