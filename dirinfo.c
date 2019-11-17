# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/types.h>
# include <errno.h>
# include <unistd.h>

char * strtype(int type);

int main() {
  DIR * dir = opendir(".");
  struct dirent * direntry = readdir(dir);
  struct stat file;
  for ( ; direntry != NULL; direntry = readdir(dir)) {
    stat(direntry->d_name, &file);
    printf("%s %ldB %s\n", strtype(direntry->d_type), file.st_size, direntry->d_name);
  }
}

char * strtype(int type) {
  if (type == 4) return "d";
  if (type == 8) return "-";
  return "?";
}
