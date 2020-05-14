all:
	gcc -c dining-p.c -Wall -Wextra
	gcc -o dining-p dining-p.c -lpthread
	gcc dining-p.c -o dining-p -lpthread

dining-p:
	gcc -c dining-p.c -Wall -Wextra
	gcc -o dining-p dining-p.c -lpthread
	gcc dining-p.c -o dining-p -lpthread
clean:
	rm dining-p dining-p.o
