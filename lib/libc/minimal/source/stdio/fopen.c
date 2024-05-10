#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zephyr/fs/fs.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/fdtable.h>

FILE* zephyr_fopen(const char* filename, const char* mode) 
{
    size_t mode_len = strlen(mode);
    if(mode_len <= 0 || mode_len >= 3) {
        return NULL;
    } 
    
    int flag = 0;
    bool destory_file_contents = false;
    
    switch (mode[0])
    {
        case 'r':
            flag = FS_O_READ;
            break;
        case 'w':
            flag = FS_O_WRITE | FS_O_CREATE;
            destory_file_contents = true;
            break;
        case 'a':
            flag = FS_O_APPEND | FS_O_CREATE;
            break;
        default:
            return NULL;
    }

    if(mode_len == 2)
    {
        if(mode[1] == '+') {
            flag = flag | FS_O_RDWR;
        }
        else {
            return NULL;
        }
    }

    int fd = z_reserve_fd();
    if(fd < 0) {
        return NULL;
    }

    struct fs_file_t zfs_file;
	fs_file_t_init(&zfs_file);
    int rc = fs_open(&zfs_file, filename, flag);
    if(rc != 0) {
        z_free_fd(fd);
        return NULL;
    }

    if(destory_file_contents) {
        fs_truncate(&zfs_file, 0);
    }

    FILE* file_rep = malloc(sizeof(FILE));
    file_rep->fd = fd;
    file_rep->file_ref = zfs_file;
    return file_rep;
}

FILE* fopen(const char* filename, const char* mode) 
{
    return zephyr_fopen(filename, mode);
}
