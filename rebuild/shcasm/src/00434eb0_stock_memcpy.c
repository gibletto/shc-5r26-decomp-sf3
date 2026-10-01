#include "decls.h"
#include "imports.h"

// entry: 00434eb0
// name : stock_memcpy
// size : 285
// sig  : void * stock_memcpy(void * _Dst, void * _Src, size_t _Size)


/* Library Function - Multiple Matches With Different Base Names
    _memcpy
    _memmove
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int * __cdecl stock_memcpy(void *_Dst,void *_Src,size_t _Size)

{
  uint left;
  int in_EDX;
  uint n;
  undefined4 *puVar1;
  undefined1 *puVar2;
  undefined4 *dst_dw;
  undefined1 *puVar3;
  
  if ((_Src < _Dst) && (_Dst < (void *)((int)_Src + _Size))) {
    puVar1 = (undefined4 *)((int)_Src + _Size);
    dst_dw = (undefined4 *)((int)_Dst + _Size);
    if (((uint)dst_dw & 3) == 0) {
      left = _Size >> 2;
      while( true ) {
        dst_dw = dst_dw + -1;
        puVar1 = puVar1 + -1;
        if (left == 0) break;
        left = left - 1;
        *dst_dw = *puVar1;
      }
      switch(_Size & 3) {
      case 1:
switchD_00434f79_caseD_1:
        *(undefined1 *)((int)dst_dw + 3) = *(undefined1 *)((int)puVar1 + 3);
        return _Dst;
      case 2:
switchD_00434f79_caseD_2:
        *(undefined2 *)((int)dst_dw + 2) = *(undefined2 *)((int)puVar1 + 2);
        return _Dst;
      case 3:
switchD_00434f79_caseD_3:
        *(undefined2 *)((int)dst_dw + 2) = *(undefined2 *)((int)puVar1 + 2);
        *(undefined1 *)((int)dst_dw + 1) = *(undefined1 *)((int)puVar1 + 1);
        return _Dst;
      }
    }
    else {
      puVar2 = (undefined1 *)((int)puVar1 + -1);
      puVar3 = (undefined1 *)((int)dst_dw + -1);
      if (_Size < 0xd) {
        for (; _Size != 0; _Size = _Size - 1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + -1;
          puVar3 = puVar3 + -1;
        }
        return _Dst;
      }
      n = -in_EDX & 3;
      left = _Size - n;
      for (; n != 0; n = n - 1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + -1;
        puVar3 = puVar3 + -1;
      }
      puVar1 = (undefined4 *)(puVar2 + -3);
      dst_dw = (undefined4 *)(puVar3 + -3);
      for (n = left >> 2; n != 0; n = n - 1) {
        *dst_dw = *puVar1;
        puVar1 = puVar1 + -1;
        dst_dw = dst_dw + -1;
      }
      switch(left & 3) {
      case 1:
        goto switchD_00434f79_caseD_1;
      case 2:
        goto switchD_00434f79_caseD_2;
      case 3:
        goto switchD_00434f79_caseD_3;
      }
    }
    return _Dst;
  }
  puVar1 = _Dst;
  if (((uint)_Dst & 3) == 0) {
    for (left = _Size >> 2; left != 0; left = left - 1) {
      *puVar1 = *(undefined4 *)_Src;
      _Src = (undefined4 *)((int)_Src + 4);
      puVar1 = puVar1 + 1;
    }
    switch(_Size & 3) {
    case 1:
switchD_00434ee0_caseD_1:
      *(undefined1 *)puVar1 = *(undefined1 *)_Src;
      return _Dst;
    case 2:
switchD_00434ee0_caseD_2:
      *(undefined2 *)puVar1 = *(undefined2 *)_Src;
      return _Dst;
    case 3:
switchD_00434ee0_caseD_3:
      *(undefined2 *)puVar1 = *(undefined2 *)_Src;
      *(undefined1 *)((int)puVar1 + 2) = *(undefined1 *)((int)_Src + 2);
      return _Dst;
    }
  }
  else {
    puVar2 = _Dst;
    if (_Size < 0xd) {
      for (; _Size != 0; _Size = _Size - 1) {
        *puVar2 = *(undefined1 *)_Src;
        _Src = (undefined1 *)((int)_Src + 1);
        puVar2 = puVar2 + 1;
      }
      return _Dst;
    }
    n = -(int)_Dst & 3;
    left = _Size - n;
    for (; n != 0; n = n - 1) {
      *(undefined1 *)puVar1 = *(undefined1 *)_Src;
      _Src = (undefined4 *)((int)_Src + 1);
      puVar1 = (undefined4 *)((int)puVar1 + 1);
    }
    for (n = left >> 2; n != 0; n = n - 1) {
      *puVar1 = *(undefined4 *)_Src;
      _Src = (undefined4 *)((int)_Src + 4);
      puVar1 = puVar1 + 1;
    }
    switch(left & 3) {
    case 1:
      goto switchD_00434ee0_caseD_1;
    case 2:
      goto switchD_00434ee0_caseD_2;
    case 3:
      goto switchD_00434ee0_caseD_3;
    }
  }
  return _Dst;
}



