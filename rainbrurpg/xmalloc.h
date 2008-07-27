/** \file xmalloc.h
  * Prototypes for functions defined in xmalloc.c  
  *
  * xmalloc is replacement of maloc with out ot memory checking.
  *
  */

VOID *xmalloc (size_t n);
VOID *xcalloc (size_t n, size_t s);
VOID *xrealloc (VOID *p, size_t n);
char *xstrdup (char *p);
