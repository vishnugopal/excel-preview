## Description

excel-preview is a small C command-line tool to preview xls or xlsx files.

It outputs the sheet name and the first ten rows from each Excel sheet.

$ excel-preview /path/to/file.xls
Sheet: Sheet1
9822382285  Vishnu  9822382286                
9822382315  Gopal 9822382316                
9822382326  Hari  9822382327                
9822382345  Sanjay  9822382346                
9822382352    9822382353                
9822382383    9822382384                
9822382420    9822382421                
9822382472    9822382473                
9822382489    9822382490                
9822382507    9822382508                

(Each sheet begins with Sheet: and columns are separated by \t. Should be easy to parse!)

## Install

Download libxl from: http://libxl.com/download.html and extrac to ./libxl

$ wget "http://libxl.com/download/libxl.tar.gz"

You need libxml-mac.tar.gz instead if you're on OSX.

$ tar -xvzf libxl.tar.gz
$ rm libxl.tar.gz
$ mv libxl-X.X.X libxl
$ make
$ sudo make install

## Uninstall

$ sudo make uninstall

