/* xmalloc.c -- malloc with out of memory checking
   Copyright (C) 1990, 91, 92, 93, 94, 95, 96, 99 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

/** \file xmalloc.c
  * Implementation of functions defined in xmalloc.h  
  *
  * xmalloc is replacement of maloc with out ot memory checking.
  *
  */

#if HAVE_CONFIG_H
# include <config.h>
#endif

/** \def VOID
  * Defines return type of xmalloc functions
  *
  * It is either declared as \c void or char, according to the presence of
  * \c __STDC__ macro.
  *
  */
#if __STDC__
# define VOID void
#else
# define VOID char
#endif

#include <stdio.h>		/* for stderr */

#if STDC_HEADERS

#include <sys/types.h>
#include <string.h>		/* for strlen etc. */
#include <stdlib.h>

#else  /* !STDC_HEADERS */

/** Definition of the standard strlen function
  *
  * This function is defined here if we do not have standard header. This
  * function is usually defined in the \c string.h header file.
  *
  */
extern size_t strlen ();

/** Definition of the standard strcpy function
  *
  * This function is defined here if we do not have standard header. This
  * function is usually defined in the \c string.h header file.
  *
  */
extern char *strcpy ();

/** Definition of the standard calloc function
  *
  * This function is defined here if we do not have standard header. This
  * function is usually defined in the \c stdlib.h header file.
  *
  */
VOID *calloc ();

/** Definition of the standard malloc function
  *
  * This function is defined here if we do not have standard header. This
  * function is usually defined in the \c stdlib.h header file.
  *
  */
VOID *malloc ();

/** Definition of the standard realloc function
  *
  * This function is defined here if we do not have standard header. This
  * function is usually defined in the \c stdlib.h header file.
  *
  */
VOID *realloc ();

/** Definition of the standard free function
  *
  * This function is defined here if we do not have standard header. This
  * function is usually defined in the \c stdlib.h header file.
  *
  */
void free ();
#endif

#if ENABLE_NLS
# include <libintl.h>
# define _(Text) gettext (Text)
#else
  /** Set domain for future gettext() calls 
    *
    * \param Domain The domain name
    *
    */
# define textdomain(Domain)
  /** The gettext shortcut macro
    * 
    * This macro is usually used as gettext shortcut.
    *
    * \param Text The text to be translated
    *
    */
# define _(Text) Text
#endif

#include <error.h>

/* Prototypes for functions defined here.  */
#if defined (__STDC__) && __STDC__
static VOID *fixup_null_alloc (size_t n);
VOID *xmalloc (size_t n);
VOID *xcalloc (size_t n, size_t s);
VOID *xrealloc (VOID *p, size_t n);
char *xstrdup (char *p);
#endif

/** Try to fix an allocation error
  *
  * This function exit with an error code of 1 if the allocation failed.
  *
  * \param n The size in bytes*
  *
  * \return The new memory block if allocation success
  *
  */
static VOID *
fixup_null_alloc (n)
     size_t n;
{
  VOID *p;

  p = 0;
  if (n == 0)
    p = malloc ((size_t) 1);
  if (p == 0)
    {
      /* possible revisions: release some memory and re-try, print
	 more information (e.g. line number of input file) */
      fprintf(stderr, _("RainbruRPG: Memory exhausted"));
      exit(1);
    }
  return p;
}

/** Allocate N bytes of memory dynamically, with error checking.  
  *
  * \param n The size of the block to allocate, in bytes
  *
  * \return A pointer to the memory block allocated by the function.
  *
  */
VOID *
xmalloc (n)
     size_t n;
{
  VOID *p;

  p = malloc (n);
  if (p == 0)
    p = fixup_null_alloc (n);
  return p;
}

/** Allocate memory for N elements of S bytes, with error checking.  
  *
  * \param n The number of elements to allocate
  * \param s The size of an element
  *
  * \return A pointer to the memory block allocated by the function.
  *
  */
VOID *
xcalloc (n, s)
     size_t n, s;
{
  VOID *p;

  p = calloc (n, s);
  if (p == 0)
    p = fixup_null_alloc (n);
  return p;
}

/** Change the size of an allocated block of memory P to N bytes,
  * with error checking.
  *
  * If P is NULL, run xmalloc.
  *
  * \param p The existing memory block
  * \param n The new size of memory block
  *
  * \return A pointer to the resized memory block.
  *
  */

VOID *
xrealloc (p, n)
     VOID *p;
     size_t n;
{
  if (p == 0)
    return xmalloc (n);
  p = realloc (p, n);
  if (p == 0)
    p = fixup_null_alloc (n);
  return p;
}

/** Make a copy of a string in a newly allocated block of memory. 
  *
  * \param str The C string to copy
  * 
  * \return The newly allocated block of memory containing a copy of the string
  *
  */
char *
xstrdup (str)
     char *str;
{
  VOID *p;

  p = xmalloc (strlen (str) + 1);
  strcpy (p, str);
  return p;
}
