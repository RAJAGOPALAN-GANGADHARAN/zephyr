/* stdio.h */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_LIB_LIBC_MINIMAL_INCLUDE_STDIO_H_
#define ZEPHYR_LIB_LIBC_MINIMAL_INCLUDE_STDIO_H_

#include <zephyr/toolchain.h>
#include <stdarg.h>     /* Needed to get definition of va_list */
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__FILE_defined)

#define __FILE_defined
#if defined(CONFIG_FDTABLE)
typedef struct fd_entry  FILE;
static ssize_t f_read_vmeth(void *obj, void *buffer, size_t count);
static ssize_t f_write_vmeth(void *obj, const void *buffer, size_t count);
static ssize_t f_write_vmeth(void *obj, const void *buffer, size_t count);
#else
typedef int FILE;
#endif

#endif

#if !defined(EOF)
#define EOF  (-1)
#endif

extern FILE* _stdin;
extern FILE* _stdout;
extern FILE* _stderr;

#define stdin _stdin
#define stdout _stdout
#define stderr _stderr

#define SEEK_SET	0	/* Seek from beginning of file.  */
#define SEEK_CUR	1	/* Seek from current position.  */
#define SEEK_END	2	/* Seek from end of file.  */

int __printf_like(1, 2) printf(const char *ZRESTRICT format, ...);
int __printf_like(3, 4) snprintf(char *ZRESTRICT str, size_t len,
				 const char *ZRESTRICT format, ...);
int __printf_like(2, 3) sprintf(char *ZRESTRICT str,
				const char *ZRESTRICT format, ...);
int __printf_like(2, 3) fprintf(FILE *ZRESTRICT stream,
				const char *ZRESTRICT format, ...);


int __printf_like(1, 0) vprintf(const char *ZRESTRICT format, va_list list);
int __printf_like(3, 0) vsnprintf(char *ZRESTRICT str, size_t len,
				  const char *ZRESTRICT format,
				  va_list list);
int __printf_like(2, 0) vsprintf(char *ZRESTRICT str,
				 const char *ZRESTRICT format, va_list list);
int __printf_like(2, 0) vfprintf(FILE *ZRESTRICT stream,
				 const char *ZRESTRICT format,
				 va_list ap);

void perror(const char *s);
int puts(const char *s);

int fputc(int c, FILE *stream);
int fputs(const char *ZRESTRICT s, FILE *ZRESTRICT stream);
size_t fwrite(const void *ZRESTRICT ptr, size_t size, size_t nitems,
	      FILE *ZRESTRICT stream);
int remove(const char *path);
#define putc(c, stream) fputc(c, stream)
#define putchar(c) putc(c, stdout)

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_LIB_LIBC_MINIMAL_INCLUDE_STDIO_H_ */
