/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   attributes_01.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/19 14:20:00 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/19 14:37:03 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdlib.h>

int		main(int ac, char *av[])
{
	int		ch, prev, row, col;
	FILE	*fp;
	int		y, x;

	prev = EOF;
	if (ac != 2)
	{
		printf("Usage: %s <a c file name>\n", av[0]);
		exit(1);
	}
	fp = fopen(av[1], "r");
	if (fp == NULL)
	{
		perror("Can't open input file");
		exit(1);
	}
	initscr();
	getmaxyx(stdscr, row, col);
	while ((ch = fgetc(fp)) != EOF)
	{
		getyx(stdscr, y, x);
		if (y == (row - 1))
		{
			printw("<-Press any key->");
			getch();
			clear();
			move(0, 0);
		}
		if (prev == '/' && ch == '*')
		{
			attron(A_BOLD);
			getyx(stdscr, y, x);
			move(y, x - 1);
			printw("%c%c", '/', ch);
		}
		else
			printw("%c", ch);
		refresh();
		if (prev == '*' && ch == '/')
			attroff(A_BOLD);
		prev = ch;
	}
	getch();
	endwin();
	fclose(fp);
	return (0);
}
