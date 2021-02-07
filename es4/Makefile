CFLAGS=-g -O0 -I include -I Resources/C/Unity/

all: createdir app

app: createdir bin/graph_app

createdir: 
	mkdir -p bin 
	mkdir -p build

clean:
	$(RM) -rf bin/* 
	$(RM) -rf build/*

build/adjListNode.o: src/adjListNode.c include/adjListNode.h
	$(CC) $(CFLAGS) -c src/adjListNode.c -o build/adjListNode.o


build/graph.o: src/graph.c include/graph.h build/adjListNode.o 
	$(CC) $(CFLAGS) -c src/graph.c -o build/graph.o
	

bin/graph_app: app/graph_app.c build/adjListNode.o build/graph.o 
	$(CC) $(CFLAGS) app/graph_app.c build/adjListNode.o build/graph.o -o bin/graph_app


