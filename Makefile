tmjsh: main.o parse.o shell.o
	gcc main.o parse.o shell.o -o tmjsh

main.o: main.c parse.h shell.h
	gcc -c main.c

parse.o: parse.c parse.h
	gcc -c parse.c

shell.o: shell.c shell.h
	gcc -c shell.c

.PHONY: clean run 

clean: 
	-rm *.o

run: 
	./tmjsh
