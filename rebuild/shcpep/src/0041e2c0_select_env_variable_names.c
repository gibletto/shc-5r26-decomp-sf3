#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_tmp_env_name
#define g_tmp_env_name (*(char * *)(g_sd + 0x6e1c))


// entry: 0041e2c0
// name : select_env_variable_names
// size : 99
// sig  : void select_env_variable_names(int is_cplusplus)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl select_env_variable_names(int is_cplusplus)

{
  if (is_cplusplus == 0) {
    _g_inc_env_name = s_SHC_INC_00428458;
    g_tmp_env_name = s_SHC_TMP_00428448;
    _g_lib_env_name_20 = s_SHC_LIB_00428450;
    _g_lib_env_name_24 = s_SHC_LIB_00428450;
    _g_lib_env_name_14 = s_SHC_LIB_00428450;
    _g_lib_env_name_18 = s_SHC_LIB_00428450;
    return;
  }
  _g_inc_env_name = s_SHCPP_INC_0042843c;
  g_tmp_env_name = s_SHCPP_TMP_00428424;
  _g_lib_env_name_20 = s_SHCPP_LIB_00428430;
  _g_lib_env_name_24 = s_SHCPP_LIB_00428430;
  _g_lib_env_name_14 = s_SHCPP_LIB_00428430;
  _g_lib_env_name_18 = s_SHCPP_LIB_00428430;
  return;
}



