#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_inc_env_name
#define g_inc_env_name (*(char * *)(g_sd + 0x13314))
#undef g_lib_env_name_00
#define g_lib_env_name_00 (*(char * *)(g_sd + 0x13300))
#undef g_lib_env_name_04
#define g_lib_env_name_04 (*(char * *)(g_sd + 0x13304))
#undef g_lib_env_name_0c
#define g_lib_env_name_0c (*(char * *)(g_sd + 0x1330c))
#undef g_lib_env_name_10
#define g_lib_env_name_10 (*(char * *)(g_sd + 0x13310))
#undef g_tmp_env_name
#define g_tmp_env_name (*(char * *)(g_sd + 0x13308))


// entry: 00434d30
// name : select_env_variable_names
// size : 99
// sig  : void __cdecl select_env_variable_names(int is_cplusplus)


int __cdecl select_env_variable_names(int is_cplusplus)

{
  if (is_cplusplus == 0) {
    g_inc_env_name = s_SHC_INC_004431a8;
    g_tmp_env_name = s_SHC_TMP_00443198;
    g_lib_env_name_0c = s_SHC_LIB_004431a0;
    g_lib_env_name_10 = s_SHC_LIB_004431a0;
    g_lib_env_name_00 = s_SHC_LIB_004431a0;
    g_lib_env_name_04 = s_SHC_LIB_004431a0;
    return;
  }
  g_inc_env_name = s_SHCPP_INC_0044318c;
  g_tmp_env_name = s_SHCPP_TMP_00443174;
  g_lib_env_name_0c = s_SHCPP_LIB_00443180;
  g_lib_env_name_10 = s_SHCPP_LIB_00443180;
  g_lib_env_name_00 = s_SHCPP_LIB_00443180;
  g_lib_env_name_04 = s_SHCPP_LIB_00443180;
  return;
}
