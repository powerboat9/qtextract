qtextract: src/main.c build/so.o
	gcc -Wall -o qtextract src/main.c build/so.o

build/so-raw.so: src/so.cpp
	g++ -fPIC -Wall -shared -I/usr/include/qt5 -o $@ $^

build/so.o: build/so-raw.so
	ld -r -b binary -o $@ $^

clean:
	rm build/* || true
	rm qtextract || true

