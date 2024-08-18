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
#include <zephyr/fs/fs_interface.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__FILE_defined)
#define __FILE_defined
typedef struct {
	/* File descriptor vended by zephyr fd table */
	int _fd;
	/* Underlying file - zfs file */
	struct fs_file_t _fs_file;
	/* Error code while reading, writing */
	int _error_bit;
} FILE;
#endif

#if !defined(EOF)
#define EOF  (-1)
#endif

const struct FILE* stdin_file = (&(FILE) {._fd = 1});
const struct FILE* stdout_file = (&(FILE) {._fd = 2});
const struct FILE* stderr_file = (&(FILE) {._fd = 3});

#define stdin  stdin_file
#define stdout stdout_file
#define stderr stderr_file

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
FILE* fopen(const char * filename,
                   const char * mode);
size_t fwrite(const void *ZRESTRICT ptr, size_t size, size_t nitems,
	      FILE *ZRESTRICT stream);
size_t fread(void *restrict ptr, size_t size, size_t nitems,
		 FILE *restrict stream);
#define putc(c, stream) fputc(c, stream)
#define putchar(c) putc(c, stdout)

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_LIB_LIBC_MINIMAL_INCLUDE_STDIO_H_ */
