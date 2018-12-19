#include <ncurses.h>

int		main()
{
	initscr();
	cbreak();
	printw("Hello, World !");
	refresh();
	getch();
	endwin();

	return (0);
}
