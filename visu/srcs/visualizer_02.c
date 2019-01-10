/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   visualizer_02.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 18:16:19 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 19:27:36 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

void	write_matrix(WINDOW *matrix, int proc_id, unsigned int pos,
		unsigned char c)
{
	unsigned int	row;
	unsigned int	col;

	row = 1 + (pos / 64);
	col = 1 + (3 * (pos % 64));
	wattron(matrix, COLOR_PAIR(3 + (-proc_id - 1)));
	mvwaddch(matrix, row, col, nibble_to_char(c >> 4));
	mvwaddch(matrix, row, col + 1, nibble_to_char(c & 0x0f));
	wattroff(matrix, COLOR_PAIR(3 + (-proc_id - 1)));
	wrefresh(matrix);
}

void	write_matrix2(WINDOW *matrix, int start, int val, int proc_id)
{
	int				i;
	int				pos;
	unsigned char	c;

	i = 0;
	while (i < REG_SIZE)
	{
		pos = (MEM_SIZE + start - i) % MEM_SIZE;
		c = (val >> (i * 8)) & 0xff;
		write_matrix(matrix, proc_id, pos, c);
		i++;
	}
}

void	update_visu(t_vm *vm)
{

	usleep(500);
}
