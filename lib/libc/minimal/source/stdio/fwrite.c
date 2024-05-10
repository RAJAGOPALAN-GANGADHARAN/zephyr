// #include <stdio.h>
// #include <zephyr/sys/libc-hooks.h>
// #include <zephyr/internal/syscall_handler.h>
// #include <string.h>
// #include <zephyr/fs/fs.h>

// size_t z_impl_zephyr_fwrite(const void *ZRESTRICT ptr, size_t size,
// 			    size_t nitems, FILE *ZRESTRICT stream)
// {
// 	size_t total_bytes = size * nitems;
	
// 	int rc = fs_write(&stream->file_ref, ptr, total_bytes);
// // 	size_t i;
// // 	size_t j;
// // 	const unsigned char *p;

// // 	if ((stream != stdout && stream != stderr) ||
// // 	    (nitems == 0) || (size == 0)) {
// // 		return 0;
// // 	}

// // 	p = ptr;
// // 	i = nitems;
// // 	do {
// // 		j = size;
// // 		do {
// // 			if (_stdout_hook((int) *p++) == EOF) {
// // 				goto done;
// // 			}
// // 			j--;
// // 		} while (j > 0);

// // 		i--;
// // 	} while (i > 0);

// // done:
// // 	return (nitems - i);
// return rc;
// }

// #ifdef CONFIG_USERSPACE
// static inline size_t z_vrfy_zephyr_fwrite(const void *ZRESTRICT ptr,
// 					  size_t size, size_t nitems,
// 					  FILE *ZRESTRICT stream)
// {

// 	K_OOPS(K_SYSCALL_MEMORY_ARRAY_READ(ptr, nitems, size));
// 	return z_impl_zephyr_fwrite((const void *ZRESTRICT)ptr, size,
// 				    nitems, (FILE *ZRESTRICT)stream);
// }
// #include <syscalls/zephyr_fwrite_mrsh.c>
// #endif

// size_t fwrite(const void *ZRESTRICT ptr, size_t size, size_t nitems,
// 			  FILE *ZRESTRICT stream)
// {
// 	return zephyr_fwrite(ptr, size, nitems, stream);
// }