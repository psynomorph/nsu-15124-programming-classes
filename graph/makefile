FLAGS= -O2 -std=gnu99

all: spanning_tree dijckstra

clean:
	rm spanning_tree dijckstra
	rm bin/*.o

spanning_tree: bin/spanning_tree.o bin/graphs.o
	gcc bin/spanning_tree.o bin/graphs.o -o spanning_tree

dijckstra: bin/dijckstra.o bin/graphs.o
	gcc bin/dijckstra.o bin/graphs.o -o dijckstra

bin/dijckstra.o: dijckstra.c graphs.h
	gcc $(FLAGS) -c dijckstra.c -o bin/dijckstra.o

bin/spanning_tree.o: spanning_tree.c graphs.h
	gcc $(FLAGS) -c spanning_tree.c -o bin/spanning_tree.o

bin/graphs.o: graphs.c graphs.h
	gcc $(FLAGS) -c graphs.c -o bin/graphs.o
