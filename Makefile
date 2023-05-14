run_linkedList:
	gcc -o linked_list.o linked_list.c
	./linked_list.o

run_dictionary:
	gcc -o dictionary.o dictionary.c
	./dictionary.o

run_ftoa:
	gcc -o ftoa.o ftoa.c
	./ftoa.o

clean:
	rm *.o