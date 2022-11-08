shf: main.o keyboardHelper.o controls.o screenHelper.o visualFileSystem.o
	gcc -o shf main.o keyboardHelper.o controls.o screenHelper.o visualFileSystem.o

main.o: main.c 
	gcc -c -o main.o main.c

keyboardHelper.o: keyboardHelper.c
	gcc -c -o keyboardHelper.o keyboardHelper.c

screenHelper.o: screenHelper.c
	gcc -c -o screenHelper.o screenHelper.c

controls.o: controls.c
	gcc -c -o controls.o controls.c

clean: 
	rm *.o
