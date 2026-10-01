#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_env_inc_name
#define g_env_inc_name (*(char * *)(g_sd + 0x27324))
#undef g_env_lib_name_1
#define g_env_lib_name_1 (*(char * *)(g_sd + 0x27310))
#undef g_env_lib_name_2
#define g_env_lib_name_2 (*(char * *)(g_sd + 0x27314))
#undef g_env_lib_name_3
#define g_env_lib_name_3 (*(char * *)(g_sd + 0x2731c))
#undef g_env_lib_name_4
#define g_env_lib_name_4 (*(char * *)(g_sd + 0x27320))
#undef g_env_tmp_name
#define g_env_tmp_name (*(char * *)(g_sd + 0x27318))


// entry: 00428bd0
// name : select_env_var_names
// size : 99
// sig  : void select_env_var_names(int is_cpp)


int __cdecl select_env_var_names(int is_cpp)

{
  if (is_cpp == 0) {
    g_env_inc_name = s_SHC_INC_00436008;
    g_env_tmp_name = s_SHC_TMP_00435ff8;
    g_env_lib_name_3 = s_SHC_LIB_00436000;
    g_env_lib_name_4 = s_SHC_LIB_00436000;
    g_env_lib_name_1 = s_SHC_LIB_00436000;
    g_env_lib_name_2 = s_SHC_LIB_00436000;
    return;
  }
  g_env_inc_name = s_SHCPP_INC_00435fec;
  g_env_tmp_name = s_SHCPP_TMP_00435fd4;
  g_env_lib_name_3 = s_SHCPP_LIB_00435fe0;
  g_env_lib_name_4 = s_SHCPP_LIB_00435fe0;
  g_env_lib_name_1 = s_SHCPP_LIB_00435fe0;
  g_env_lib_name_2 = s_SHCPP_LIB_00435fe0;
  return;
}



