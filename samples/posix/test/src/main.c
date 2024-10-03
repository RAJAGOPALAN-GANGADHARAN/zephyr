// #include<stdio.h>
// #include <string.h>
// #include <signal.h>
// #include <zephyr/fs/fs.h>
// #include <ff.h>

// #define FATFS_MNTP	"/RAM:"
// #define TEST_ROOT	FATFS_MNTP"/"
// #define TEST_FILE	FATFS_MNTP"/testfile.txt"
// #define TEST_DIR	FATFS_MNTP"/testdir"
// #define TEST_DIR_FILE	FATFS_MNTP"/testdir/testfile.txt"
// /* FatFs work area */
// static FATFS fat_fs;

// /* mounting info */
// static struct fs_mount_t fatfs_mnt = {
// 	.type = FS_FATFS,
// 	.mnt_point = FATFS_MNTP,
// 	.fs_data = &fat_fs,
// };

// void test_mount(void)
// {
// 	int res;

// 	res = fs_mount(&fatfs_mnt);
// 	if (res < 0) {
// 		printf("Error mounting fs [%d]\n", res);
// 		/* FIXME: restructure tests as per #46897 */
// 		__ASSERT_NO_MSG(res == 0);
// 	}

// 	return NULL;
// }

// int main () {
//    FILE *fp;
//    char data[] = "Test file\n";
//     char buffer[100];
//    test_mount();

//    fp = fopen( "/RAM:/file.txt" , "w+" );
//    if(fp == NULL) {
//       printf("Unable to open the file\n");
//    } else {
//       printf("Opened the file bruh!\n");
//    }
//     int bytes_written = fwrite(data, sizeof(data[0]), sizeof(data) - 1, fp);

   
//     if (bytes_written != sizeof(data) - 1) {
//         perror("fwrite failed");
//         fs_close(&fp->_fs_file);
//         return 1;
//     }
//    //  fs_close(&fp->file_ref);
//     fs_sync(&fp->_fs_file);
//    //     size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, fp);
//    //   buffer[bytes_read] = '\0';
//    FILE* fp2 = fopen("/RAM:/file.txt", "r");
//    printf("Opened the file bruh - 4!\n");
//     if (fp2 == NULL) {
//         perror("fopen failed");
//         return 1;
//     }
//     size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, fp2);
//      buffer[bytes_read] = '\0';

//    //  // Print the read data
//     printf("Read data: %s - %d\n", buffer, bytes_read);


// // 	fs_close(&file);
  
//    return(0);
// }





#include<stdio.h>

int main()
{
    printf("Hello1");
    fprintf(stdin, "Hello");
    fputc('c', stdout);
    return 0;
}