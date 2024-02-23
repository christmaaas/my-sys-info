all:
	gcc -g src/main.c TUI/main_window.c -o MySysInfo.exe -lncurses -lpanel