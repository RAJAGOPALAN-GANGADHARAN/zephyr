/* stdin_fread.c */

#include <stdio.h>
#include <zephyr/sys/libc-hooks.h>
#include <zephyr/fs/fs.h>
#include <zephyr/internal/syscall_handler.h>

size_t z_impl_zephyr_fread(const void *ZRESTRICT buffer, size_t size,
			    size_t nitems, FILE *ZRESTRICT stream)
{
	size_t total_bytes = size * nitems;
	if(total_bytes == 0)
	{
		stream->error_bit = 0;
		return 0;
	}
	ssize_t rc = fs_read(&stream->file_ref, buffer, total_bytes);
	if(rc < 0)
	{
		stream->error_bit = -rc;
	}
	return rc;
}

size_t fread(const void *ZRESTRICT buffer, size_t size, size_t nitems,
			  FILE *ZRESTRICT stream)
{
	return zephyr_fread(buffer, size, nitems, stream);
}
