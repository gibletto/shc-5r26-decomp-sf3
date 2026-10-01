#ifndef GHIDRA_STUBS_H
#define GHIDRA_STUBS_H
/* The types and pseudo-operations Ghidra's C uses. Included first by every source (decls.h). */
#define WIN32_LEAN_AND_MEAN
#include <stddef.h>
/* Visual C++ 6 has no <stdint.h> */
typedef signed char        int8_t;
typedef unsigned char      uint8_t;
typedef short              int16_t;
typedef unsigned short     uint16_t;
typedef int                int32_t;
typedef unsigned int       uint32_t;
typedef __int64            int64_t;
typedef unsigned __int64   uint64_t;
#include <stdio.h>
#include <windows.h>

typedef unsigned char      byte;
typedef unsigned char      undefined;
typedef unsigned char      undefined1;
typedef unsigned short     undefined2;
typedef unsigned int       undefined3;
typedef unsigned int       undefined4;
typedef unsigned __int64   undefined8;
typedef unsigned short     ushort;
typedef unsigned int       uint;
typedef unsigned long      ulong;
typedef unsigned __int64   ulonglong;
typedef __int64            longlong;
typedef unsigned short     word;
typedef unsigned int       dword;
typedef unsigned char      uchar;
typedef int                int3;

/* `code *` is Ghidra's function pointer; as FARPROC, so GetProcAddress results assign without a cast */
typedef INT_PTR __stdcall  code();

/* Ghidra's bool */
#ifndef __cplusplus
#ifndef _STDBOOL
#define bool int
#define true 1
#define false 0
#define _STDBOOL
#endif
#endif

/* Ghidra names Win32 structs by their tag (`_STARTUPINFOA local_10;`) */
typedef struct _STARTUPINFOA       _STARTUPINFOA;
typedef struct _SECURITY_ATTRIBUTES _SECURITY_ATTRIBUTES;
typedef struct _cpinfo             _cpinfo;

/* types Visual C++ 6's headers lack */
#if _MSC_VER < 1300
typedef int                intptr_t;
typedef unsigned int       uintptr_t;
typedef void *             _locale_t;
typedef const wchar_t *    PCNZWCH;
typedef const char *       PCNZCH;
#endif

/* The stock CRT's FILE record. The streams the stages open are the host CRT's (src/_crt_shim.c); this is for the
   stock CRT's own records in the stock data image. */
typedef struct _gh_iobuf {
  char *   _ptr;
  int      _cnt;
  char *   _base;
  int      _flag;
  int      _file;
  int      _charbuf;
  int      _bufsiz;
  char *   _tmpfname;
} GhFILE;

/* Ghidra's pseudo-operations: CONCATxy(a,b) joins an x-byte and a y-byte value; CARRY / SCARRY / SBORROW are the
   carry and overflow flags of an add or subtract; SUBxy(a,b) is the y bytes at byte offset b of an x-byte value */
#define CONCAT11(a,b)  ((unsigned short)((((unsigned char)(a))<<8) | (unsigned char)(b)))
#define CONCAT12(a,b)  ((unsigned int)(((unsigned int)((unsigned char)(a))<<16) | (unsigned short)(b)))
#define CONCAT13(a,b)  ((unsigned int)(((unsigned int)((unsigned char)(a))<<24) | ((unsigned int)(b) & 0xffffff)))
#define CONCAT22(a,b)  ((unsigned int)(((unsigned int)(unsigned short)(a)<<16) | (unsigned short)(b)))
#define CONCAT31(a,b)  ((unsigned int)(((unsigned int)((a) & 0xffffff)<<8) | (unsigned char)(b)))
#define CONCAT44(a,b)  ((unsigned __int64)(((unsigned __int64)(unsigned int)(a)<<32) | (unsigned int)(b)))
#define CARRY4(a,b)    ((int)(((unsigned int)(a) + (unsigned int)(b)) < (unsigned int)(a)))
#define CARRY8(a,b)    ((int)(((unsigned __int64)(a) + (unsigned __int64)(b)) < (unsigned __int64)(a)))
#define SCARRY4(a,b)   ((int)((((a) ^ (b)) & 0x80000000) == 0 && (((a) ^ ((a)+(b))) & 0x80000000) != 0))
#define SBORROW4(a,b)  ((int)((((a) ^ (b)) & 0x80000000) != 0 && (((a) ^ ((a)-(b))) & 0x80000000) != 0))
#define SUB21(a,b)     ((unsigned char)((unsigned short)(a) >> ((b) * 8)))
#define SUB41(a,b)     ((unsigned char)((unsigned int)(a) >> ((b) * 8)))
#define SUB42(a,b)     ((unsigned short)((unsigned int)(a) >> ((b) * 8)))
#define SUB81(a,b)     ((unsigned char)((unsigned __int64)(a) >> ((b) * 8)))
#define SUB84(a,b)     ((unsigned int)((unsigned __int64)(a) >> ((b) * 8)))

#endif /* GHIDRA_STUBS_H */
