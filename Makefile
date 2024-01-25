run_linkedList:
	gcc -o linked_list.o linked_list.c
	./linked_list.o

run_dictionary:
	gcc -o dictionary.o dictionary.c
	./dictionary.o

run_ftoa:
	gcc -o ftoa.o ftoa.c
	./ftoa.o

run_sort:
	gcc -o bubble_sort.o bubble_sort.c
	./bubble_sort.o

run_oop:
	gcc -o oop.o oop_in_c/*.c
	./oop.o shopping Alla
	./oop.o movie Blly

clean:
	rm -f *.o *.out