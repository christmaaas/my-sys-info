all:
	gcc -g -ggdb -std=c11 -pedantic -W -Wall -Wextra -lncurses -lpanel -o MySysInfo.out src/system/main.c src/system/cpu.c  
clean:
	rm -f *.o MySysInfo.out