/* GEN_NARROW_CONST (src/_construles.c); otherwise Release 26. */
#ifndef CONSTRULES_H
#define CONSTRULES_H
#if SHC_REBUILD_UPDATED
extern int gen_narrow_const(unsigned char type);
#define NARROW_CONST(type) gen_narrow_const(type)
#else
#define NARROW_CONST(type) 0
#endif
#endif
