#include "decls.h"
#include "imports.h"
#include <stdio.h>
#include <stdarg.h>
#include <io.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>

/* The stock CRT's stdio is replaced by the host CRT. Stock shcgen held its _iob[1]/_iob[2] (stdout/stderr) at
   0045cab0/0045cad0; a FILE * at those addresses in the data image is the host's stdout/stderr. The streams the
   stage opens itself are the host CRT's (typed GhFILE * in the stage's code, passed through as they are). */
static FILE *real_file(void *f) {
    if (f == (void *)SD(0x0045cab0)) return stdout;
    if (f == (void *)SD(0x0045cad0)) return stderr;
    return (FILE *)f;
}
#define RF(f) real_file((void *)(f))

/* Ghidra names CRT routines with a leading underscore (_fclose); C decoration adds another. */

int _fclose(GhFILE *f) { return fclose(RF(f)); }
int _fflush(GhFILE *f) { return fflush(RF(f)); }
int _fputc(int c, GhFILE *f) { return fputc(c, RF(f)); }
int _fputs(const char *s, GhFILE *f) { return fputs(s, RF(f)); }
void _rewind(GhFILE *f) { rewind(RF(f)); }

int _sprintf(char *buf, const char *fmt, ...) {
    int r; va_list ap; va_start(ap, fmt); r = vsprintf(buf, fmt, ap); va_end(ap); return r;
}
char *_tmpnam(char *s) { return tmpnam(s); }

size_t __fread_lk(void *buf, size_t elt, size_t cnt, GhFILE *f) { return fread(buf, elt, cnt, RF(f)); }
GhFILE *__fsopen(const char *name, const char *mode, int shflag) { return (GhFILE *)_fsopen(name, mode, shflag); }
int __flush(GhFILE *f) { return fflush(RF(f)); }
char *__getbuf(GhFILE *f) { (void)f; return NULL; }
int __chsize(int fd, long sz) { return _chsize(fd, sz); }
int __close(int fd) { return _close(fd); }
int __isctype(int c, int t) { return _isctype(c, t); }
int _signal(int s, void *h) { return (int)signal(s, (void (__cdecl *)(int))h); }
/* the stock CRT's fatal-message box: the host CRT has its own */
int ___crtMessageBoxA(void) { return 0; }
/* Ghidra's name for an inlined strncpy */
char *builtin_strncpy(char *d, const char *s, size_t n) { return strncpy(d, s, n); }
/* the stock CRT's fwrite, fseek and doexit (0043ab90, 0043a860, 0043a7c0): the rebuild's streams are
   the host CRT's (the stock lseek walks the stock handle table, which never holds them), and exit runs the host
   CRT's atexit/flush instead of the stock _initterm tables (stock code addresses) */
unsigned int stock_fwrite(char *buf, unsigned int size, unsigned int n, void *f) { return fwrite(buf, size, n, RF(f)); }
int stock_fseek(void *f, long off, int whence) { return fseek(RF(f), off, whence); }
int stock_doexit(unsigned int code, int quick, int retcaller) {
    (void)quick;
    if (retcaller == 0) exit((int)code);
    return 0;
}
