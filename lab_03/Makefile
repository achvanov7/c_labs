flaggs = gcc -Werror -Wall -Wextra -c
all: lab_03

main:
	$(flaggs) src/main.c -o obj/main.o -I include

clist: 
	$(flaggs) src/clist.c -o obj/clist.o -I include

lab_03: main clist
	gcc obj/main.o obj/clist.o -o lab_03

clean:
	rm -rf obj/*.o lab_03
