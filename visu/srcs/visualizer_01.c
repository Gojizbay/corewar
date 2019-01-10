/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   visualizer_01.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 11:41:31 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 19:27:35 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

t_win	*init_windows(void)
{
	t_win	*windows;

	if (!(windows = ft_memalloc(sizeof(t_win))))
		return (NULL);
	init_color(COLOR_CYAN, 242, 242, 242);
	init_pair(1, COLOR_BLACK, COLOR_CYAN);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	if (!(windows->wrap = newwin(WRAP_H, WRAP_W, WRAP_SY, WRAP_SX)))
		return (NULL);
	wbkgd(windows->wrap, COLOR_PAIR(1));
	wrefresh(windows->wrap);
	if (!(windows->matrix = newwin(MATRIX_H, MATRIX_W, MATRIX_SY, MATRIX_SX)))
		return (NULL);
	wbkgd(windows->matrix, COLOR_PAIR(2));
	wrefresh(windows->matrix);
	if (!(windows->info = newwin(INFO_H, INFO_W, INFO_SY, INFO_SX)))
		return (NULL);
	wbkgd(windows->info, COLOR_PAIR(2));
	wrefresh(windows->info);
	return (windows);
}

void	close_windows(t_win *win)
{
	getch();
	delwin(win->wrap);
	delwin(win->matrix);
	delwin(win->info);
	free(win);
	endwin();
}

void	start_visualizer(t_vm *vm)
{
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	if (!has_colors())
	{
		/*error message*/
		exit(EXIT_FAILURE);
	}
	start_color();
	refresh();
	if (!(vm->win = init_windows()))
	{
		/*error message*/
		exit(EXIT_FAILURE);
	}
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	display_memory(vm);
}

char	nibble_to_char(unsigned char ch)
{
	return ((ch < 10) ? ch + '0' : ch - 10 + 'a');
}

void	display_memory(t_vm *vm)
{
	unsigned char	*mem;
	int				i;
	int				row;
	int				col;

	mem = vm->mem;
	i = 0;
	row = 1;
	col = 1;
	while (i < MEM_SIZE)
	{
		
		mvwaddch(vm->win->matrix, row, col++, nibble_to_char(mem[i] >> 4));
		mvwaddch(vm->win->matrix, row, col++, nibble_to_char(mem[i] & 0x0f));
		col++;
		i++;
		if (i % 64 == 0)
		{
			col = 1;
			row++;
		}
	}
	wrefresh(vm->win->matrix);
}
