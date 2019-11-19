# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/types.h>
# include <errno.h>
# include <unistd.h>

char * strtype(int type);

int main(int argc, char * argv[]) {
  char dir_to_scan[256];
  if (argv[1] == NULL) {
    printf("Please enter a directory to scan: \n");
    fgets(dir_to_scan, 256, stdin);
    dir_to_scan[strlen(dir_to_scan) - 1] = 0;
  }
  else {
    strcpy(dir_to_scan, argv[1]);
  }
  DIR * dir = opendir(dir_to_scan);
  if (dir == NULL) {
    printf("Error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  int dir_size = 0;
  struct dirent * direntry = readdir(dir);
  struct stat file;
  for ( ; direntry != NULL; direntry = readdir(dir)) {
    stat(direntry->d_name, &file);
    if (direntry->d_type == 8) {
      dir_size += file.st_size;
    }
    printf("%s %ldB %s\n", strtype(direntry->d_type), file.st_size, direntry->d_name);
  }
  printf("Total dir size: %dB\n", dir_size);
}

char * strtype(int type) {
  if (type == 4) return "d";
  if (type == 8) return "-";
  return "?";
}
