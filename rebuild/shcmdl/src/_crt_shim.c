#include "decls.h"
#include "imports.h"
#include <stdio.h>
#include <stdarg.h>
#include <io.h>
#include <ctype.h>
#include <signal.h>

/* As rebuild/shcpep/src/_crt_shim.c: the stock CRT's stdio (FILE records in the stock data image) is replaced by
   the host CRT. Stock shcmdl held its _iob[1]/_iob[2] (stdout/stderr) at 004360e8/00436108; any FILE * at those
   addresses is the real stdout/stderr. */
static FILE *real_file(void *f) {
    if (f == (void *)SD(0x004360e8)) return stdout;
    if (f == (void *)SD(0x00436108)) return stderr;
    return (FILE *)f;
}
#define RF(f) real_file((void *)(f))

/* Ghidra names CRT routines with a leading underscore (_fclose); C decoration adds another. */
int _fclose(void *f) { return fclose(RF(f)); }
int _fflush(void *f) { return fflush(RF(f)); }
int _fputc(int c, void *f) { return fputc(c, RF(f)); }
int _fputs(const char *s, void *f) { return fputs(s, RF(f)); }
int _rewind(void *f) { rewind(RF(f)); return 0; }
int _sprintf(char *buf, const char *fmt, ...) {
    int r; va_list ap; va_start(ap, fmt); r = vsprintf(buf, fmt, ap); va_end(ap); return r;
}
int FID_conflict__wprintf(const char *fmt, ...) {          /* _printf */
    int r; va_list ap; va_start(ap, fmt); r = vprintf(fmt, ap); va_end(ap); return r;
}
int FID_conflict__fwprintf(void *f, const char *fmt, ...) { /* _fprintf */
    int r; va_list ap; va_start(ap, fmt); r = vfprintf(RF(f), fmt, ap); va_end(ap); return r;
}
char *_tmpnam(char *s) { return tmpnam(s); }

size_t __fread_lk(void *buf, size_t elt, size_t cnt, void *f) { return fread(buf, elt, cnt, RF(f)); }
FILE *__fsopen(const char *name, const char *mode, int shflag) { return _fsopen(name, mode, shflag); }
int __flush(void *f) { return fflush(RF(f)); }
int __chsize(int fd, long sz) { return _chsize(fd, sz); }
int __close(int fd) { return _close(fd); }
int __access(const char *p, int m) { return _access(p, m); }
int __isctype(int c, int t) { return _isctype(c, t); }
int _signal(int s, void *h) { return (int)signal(s, (void (__cdecl *)(int))h); }

/* the stock CRT's fatal-message path: the host CRT has its own */
int __FF_MSGBANNER(void) { return 0; }
int ___crtMessageBoxA(void) { return 0; }
/* _alloca_probe: the host compiler probes its own frames */
int stock_alloca_probe(void) { return 0; }
/* _fwrite_lk */
unsigned int stock_fwrite_lk(char *buf, unsigned int size, unsigned int n, void *f) { return fwrite(buf, size, n, RF(f)); }
int FID_conflict___toupper_lk(int c) { return toupper(c); }
/* fseek: the stock routine's lseek walks the stock runtime's handle table, which never holds the host CRT's streams */
int stock_fseek(void *f, long off, int whence) { return fseek(RF(f), off, whence); }
/* _flsbuf: the code's inline putc on the stock image's stdout record (its count stays below 0) ends here */
int stock_flsbuf(int c, void *f) { return fputc(c, RF(f)); }
/* ftell: as fseek, the stock routine's lseek cannot see the host CRT's streams */
long stock_ftell(void *f) { return ftell(RF(f)); }
