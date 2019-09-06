llist.o: llist.cpp
	g++ -ansi -pedantic-errors -Wall -c llist.cpp

main.o: main.cpp
	g++ -ansi -pedantic-errors -Wall -c main.cpp

menuoptions.o: menuoptions.cpp
	g++ -ansi -pedantic-errors -Wall -c menuoptions.cpp

llist_debug.o: llist_debug.cpp
	g++ -ansi -pedantic-errors -Wall -c llist_debug.cpp

project2: llist.o menuoptions.o main.o
	g++ -o project2 main.o menuoptions.o llist.o

project2_debug: main.o menuoptions.o llist_debug.o
	g++ -o project2_debug main.o menuoptions.o llist_debug.o
