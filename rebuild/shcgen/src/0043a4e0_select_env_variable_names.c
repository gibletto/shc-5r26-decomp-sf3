#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_inc_env_name
#define g_inc_env_name (*(char * *)(g_sd + 0x1ff78))
#undef g_lib_env_name_14
#define g_lib_env_name_14 (*(char * *)(g_sd + 0x1ff64))
#undef g_lib_env_name_18
#define g_lib_env_name_18 (*(char * *)(g_sd + 0x1ff68))
#undef g_lib_env_name_20
#define g_lib_env_name_20 (*(char * *)(g_sd + 0x1ff70))
#undef g_lib_env_name_24
#define g_lib_env_name_24 (*(char * *)(g_sd + 0x1ff74))
#undef g_tmp_env_name
#define g_tmp_env_name (*(char * *)(g_sd + 0x1ff6c))


// entry: 0043a4e0
// name : select_env_variable_names
// size : 99
// sig  : void select_env_variable_names(int is_cplusplus)


int __cdecl select_env_variable_names(int is_cplusplus)

{
  if (is_cplusplus == 0) {
    g_inc_env_name = s_SHC_INC_0045ca18;
    g_tmp_env_name = s_SHC_TMP_0045ca08;
    g_lib_env_name_20 = s_SHC_LIB_0045ca10;
    g_lib_env_name_24 = s_SHC_LIB_0045ca10;
    g_lib_env_name_14 = s_SHC_LIB_0045ca10;
    g_lib_env_name_18 = s_SHC_LIB_0045ca10;
    return;
  }
  g_inc_env_name = s_SHCPP_INC_0045c9fc;
  g_tmp_env_name = s_SHCPP_TMP_0045c9e4;
  g_lib_env_name_20 = s_SHCPP_LIB_0045c9f0;
  g_lib_env_name_24 = s_SHCPP_LIB_0045c9f0;
  g_lib_env_name_14 = s_SHCPP_LIB_0045c9f0;
  g_lib_env_name_18 = s_SHCPP_LIB_0045c9f0;
  return;
}



