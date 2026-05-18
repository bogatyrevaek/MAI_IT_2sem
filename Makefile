all:
	gcc -Wall -Wextra -std=c99 sort.c -o sort

run:
	./sort

clean:
	rm -f sort
