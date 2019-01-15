/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   visualizer_04.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:59:40 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 17:42:43 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

void	change_speed(t_vm *vm, char ch)
{
	short	cps;

	cps = vm->win->cycles_per_sec;
	if (ch == 'q' || ch == 'Q')
		cps = (cps > 10) ? cps - 10 : 1;
	else if (ch == 'w' || ch == 'W')
		cps = (cps > 1) ? cps - 1 : 1;
	else if (ch == 'e' || ch == 'E')
		cps = (cps < 1000) ? cps + 1 : 1000;
	else if (ch == 'r' || ch == 'R')
		cps = (cps <= 990) ? cps + 10 : 1000;
	vm->win->cycles_per_sec = cps;
}

void	update_visu(t_vm *vm, char ch)
{
	if (ft_strchr("qQwWeErR", ch))
		change_speed(vm, ch);
	write_info_cycle(vm);
	if (ch == ' ')
	{
		write_info_par(vm);
		while ((ch = getch()) != ' ')
		{
			if (ft_strchr("qQwWeErR", ch))
			{
				change_speed(vm, ch);
				write_info_speed(vm);
			}
		}
		write_info_par(vm);
	}
	usleep(1000000 / vm->win->cycles_per_sec);
}

void	close_windows(t_win *win)
{
	nodelay(stdscr, FALSE);
	while ((getch()) != ' ')
		;
	endwin();
	free(win);
}

void	exit_error_visualizer(t_win *win)
{
	endwin();
	if (win)
		free(win);
}
