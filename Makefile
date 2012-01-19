all: excel-preview

excel-preview: excel-preview.c ./libxl/lib/libxl.dylib /usr/local/lib/libxl.dylib
	gcc -o excel-preview -I./libxl/include_c -L/usr/local/lib -lxl excel-preview.c

/usr/local/lib/libxl.dylib:
	ln -s `pwd`/libxl/lib/libxl.dylib /usr/local/lib/libxl.dylib

clean:
	rm excel-preview
	rm /usr/local/lib/libxl.dylib

install: all
	install -C excel-preview /usr/bin

uninstall:
	rm /usr/bin/excel-preview