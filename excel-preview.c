#include <stdio.h>
#include <assert.h>
#include <libxl.h>

#define HELP_TEXT "Usage: excel-preview /path/to/file.\n"

int main(int argc, char *argv[])
{
    char* file_path;

    if(argc != 2) {
      printf("Invalid arguments.\n");
      printf(HELP_TEXT);
      return 0;
    }

    // Get the file path
    file_path = argv[1];
    assert(file_path);

    return 0;
}
