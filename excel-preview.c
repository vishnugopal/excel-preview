#include <stdio.h>
#include <assert.h>
#include <libxl.h>

#define HELP_TEXT "Usage: excel-preview /path/to/file.\n"
#define MAX_ROW 10
#define MAX_COL 10

void error(BookHandle* book)
{
  const char* error = xlBookErrorMessage(*book);
  printf("Error: %s\n", error);
}

void cell_contents_as_string(char* buffer, SheetHandle sheet, int row, int col) {
  int cell_type = xlSheetCellType(sheet, row, col);
  if(cell_type == CELLTYPE_EMPTY) {
    strlcpy(buffer, "");
  } else if(cell_type == CELLTYPE_NUMBER) {
    snprintf(buffer, 30, "%ld", (long)xlSheetReadNum(sheet, row, col, 0));
  } else if (cell_type == CELLTYPE_STRING) {
    strlcpy (buffer, xlSheetReadStr(sheet, row, col, 0), 300);
  }
}

void print_cell_contents(SheetHandle sheet, int row, int col)
{
  char buffer[300];
  cell_contents_as_string(buffer, sheet, row, col);
  if(*buffer && *buffer != '\0') {
    printf("%s", buffer);
    printf("\t");
  }
}

void preview(char* file_path)
{
  BookHandle book = xlCreateBook();
  if(book) {
    if(xlBookLoad(book, file_path)) {
      SheetHandle sheet = xlBookGetSheet(book, 0);
      if(sheet) {
        int i, j;

        for(i = 0; i < MAX_ROW; i++) {
          for(j = 0; j < MAX_COL; j++) {
            print_cell_contents(sheet, i, j);
          }
          printf("\n");
        }
        
        error(&book);
      }
    }
   
    xlBookRelease(book);
  }
}

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

    preview(file_path);

    return 0;
}
