/*
 * Copyright (c) 2024 Rajagopalan Gangadharan
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <zephyr/fs/fs.h>
#include <zephyr/sys/fdtable.h>

int _convert_mode_to_flag(const char *mode)
{
    int flag = 0;
	switch (*mode++)
    {
        case 'r':
            flag = FS_O_READ;
            break;
        case 'w':
            flag = FS_O_TRUNC;
            break;
        case 'a':
            flag = FS_O_APPEND | FS_O_CREATE;
            break;
        default:
            errno = EINVAL;
            return 0;
    }

    if (*mode == '+' || (*mode == 'b' && mode[1] == '+')) {
		flag = flag | FS_O_RDWR;
	}

    return flag;
}

FILE* zephyr_fopen(const char *ZRESTRICT filename, const char *ZRESTRICT mode) 
{
    /**
     * TODO:
     * File doesnt exist
     * path too long
     * 
    */

    int flag = _convert_mode_to_flag(mode);
    if(!flag) {
        errno = EINVAL;
        return NULL;
    }

    int fd = z_reserve_fd();
    if(fd < 0) {
        errno = ENFILE;
        return NULL;
    }

    struct fs_file_t zfs_file;
	fs_file_t_init(&zfs_file);
    int rc = fs_open(&zfs_file, filename, flag);
    if(rc != 0) {
        /**
         *  TODO: Error code conversion here
         */
        z_free_fd(fd);
        return NULL;
    }

    FILE* file_rep = malloc(sizeof(FILE));
    if(file_rep == NULL) {
        errno = ENOMEM;
        z_free_fd(fd);
        fs_close(&zfs_file);
        return NULL;
    }

    if(truncate_file) {
        rc = fs_truncate(&zfs_file, 0);
        if(rc < 0) {
            /**
            *  TODO: Error code conversion here
            */
            z_free_fd(fd);
            fs_close(&zfs_file);
            return NULL;
        }
    }
    /** Finalize z fd call here*/
    
    file_rep->_fd = fd;
    file_rep->_fs_file = zfs_file;
    return file_rep;
}

FILE* fopen(const char *ZRESTRICT filename, const char *ZRESTRICT mode)
{
    return zephyr_fopen(filename, mode);
}

