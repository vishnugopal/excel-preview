all: excel-preview

excel-preview: excel-preview.c ./libxl/lib/libxl.dylib /usr/local/lib/libxl.*
	gcc -o excel-preview -I./libxl/include_c -L/usr/local/lib -lxl excel-preview.c

/usr/local/lib/libxl.*:
	ln -sv `pwd`/libxl/lib/libxl.* /usr/local/lib
	@/sbin/ldconfig 2>/dev/null || echo ' '

clean:
	rm -f excel-preview
	rm -f /usr/local/lib/libxl.*

install: all
	install -C excel-preview /usr/bin

uninstall:
	rm -f /usr/bin/excel-preview