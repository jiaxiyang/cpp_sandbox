#include "apue.h"
#include <dirent.h>

// DIR defination: typedef struct __dirstream DIR;
// https://blog.csdn.net/zhuyi2654715/article/details/7605051
// http://sourceware.org/git/?p=glibc.git;a=blob;f=sysdeps/unix/dirstream.h;h=8303f07fab6f6efaa39e51411ef924e712d995e0;hb=fa39685d5c7df2502213418bead44e9543a9b9ec

int main(int argc, char *argv[]) {
  DIR *dp;
  struct dirent *dirp;
  if (argc != 2)
    err_quit("usage: ls directory_name");

  if ((dp = opendir(argv[1])) == NULL)
    err_sys("can't open %s", argv[1]);

  while ((dirp = readdir(dp)) != NULL)
    printf("%s\n", dirp->d_name);

  closedir(dp);
  exit(0);
  // return 0;
}
