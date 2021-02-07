CFLAGS=-g -O0 -I include -I Resources/C/Unity/

all: createdir test app
test: createdir bin/sorting_test
app:  createdir bin/sorting_app

createdir: 
	mkdir -p bin 
	mkdir -p build
	mkdir -p data

clean:
	$(RM) -rf bin/* !*.csv
	$(RM) -rf build/*

build/my_array.o: src/my_array.c include/my_array.h
	$(CC) $(CFLAGS) -c src/my_array.c -o build/my_array.o

build/sorting.o: src/sorting.c build/my_array.o include/sorting.h 
	$(CC) $(CFLAGS) -c src/sorting.c -o build/sorting.o

bin/sorting_test: test/sorting_test.c build/my_array.o build/sorting.o include/sorting.h
	$(CC) $(CFLAGS) test/sorting_test.c build/my_array.o build/sorting.o Resources/C/Unity/unity.c -o bin/sorting_test

bin/sorting_app: sorting_app/sorting_app.c build/my_array.o build/sorting.o include/sorting.h
	$(CC) $(CFLAGS) sorting_app/sorting_app.c build/my_array.o build/sorting.o -o bin/sorting_app
