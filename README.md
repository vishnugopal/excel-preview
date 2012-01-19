## Description

excel-preview is a small C command-line tool to preview xls or xlsx files.

It outputs the sheet name and the first ten rows from each Excel sheet.

$ excel-preview /path/to/file.xls
Sheet: Sheet1
9822382285  Vishnu  
9822382315  Gopal 
9822382326  Hari  
9822382345  Sanjay  
9822382352  
9822382383  
9822382420  
9822382472  
9822382489  
9822382507  

## Install

Download libxl from: http://libxl.com/download.html and extrac to ./libxl

Substitute "mac" with your architecture:

$ wget "http://libxl.com/download/libxl-mac.tar.gz"
$ tar -xvzf libxl-mac.tar.gz
$ rm libxl-mac.tar.gz
$ mv libxl-3.2.3 libxl
$ make
$ sudo make install

