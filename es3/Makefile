CFLAGS=-g -O0 -I include -I Resources/C/Unity/

all: createdir test app
test: createdir bin/hashmap_test
app: createdir bin/hashmap_app

createdir: 
	mkdir -p bin 
	mkdir -p build

clean:
	$(RM) -rf bin/* 
	$(RM) -rf build/*

build/hashmap.o: src/hashmap.c include/hashmap.h
	$(CC) $(CFLAGS) -c src/hashmap.c -o build/hashmap.o

bin/hashmap_test: test/hashmap_test.c build/hashmap.o 
	$(CC) $(CFLAGS) test/hashmap_test.c build/hashmap.o Resources/C/Unity/unity.c -o bin/hashmap_test

bin/hashmap_app: app/hashmap_app.c build/hashmap.o 
	$(CC) $(CFLAGS) app/hashmap_app.c build/hashmap.o -o bin/hashmap_app


