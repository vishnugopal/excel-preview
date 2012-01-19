#include <stdio.h>
#include <assert.h>
#include <libxl.h>
#include <string.h>

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
    strlcpy(buffer, "", 1);
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
  }
  printf("\t");
}

void preview_sheet(BookHandle book, int sheet_number)
{
  SheetHandle sheet = xlBookGetSheet(book, sheet_number);
  if(sheet) {
    int j, k;

    printf("Sheet: %s\n", xlSheetName(sheet));

    for(j = 0; j < MAX_ROW; j++) {
      for(k = 0; k < MAX_COL; k++) {
        print_cell_contents(sheet, j, k);
      }
      printf("\n");
    }
  }
}

void strtolower(char *str) {
  while(*str != 0) {
    if (*str >= 'A' && *str <= 'Z') {
      *str = *str + 'a' - 'A';
    }
    str++;
  }
}

BookHandle book_from_file_path(const char* file_path) {
  char extension[3];
  int length = strlen(file_path);

  //Copy last four characters
  strlcpy(extension, file_path + length - 4, 5);

  strtolower(extension);

  if(strncmp(extension, "xlsx", 4) == 0) {
    return xlCreateXMLBook();
  } else {
    return xlCreateBook();
  }
}

void preview(char* file_path)
{
  book_from_file_path(file_path);
  BookHandle book = book_from_file_path(file_path);
  if(book) {
    if(xlBookLoad(book, file_path)) {
      int sheet_count, i;

      sheet_count = xlBookSheetCount(book);

      for(i = 0; i < sheet_count; i++) {
        preview_sheet(book, i);
      }
    } else {
      printf("Cannot load: %s\n", file_path);
      printf(HELP_TEXT);
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
