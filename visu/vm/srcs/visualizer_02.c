/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   visualizer_02.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 18:16:19 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/13 19:20:12 by bodibon     ###    #+. /#+    ###.fr     */
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

void	set_cursor_color(WINDOW *matrix, int proc_id, unsigned int pos)
{
	unsigned int	row;
	unsigned int	col;
	short			color_pair;

	row = 1 + (pos / 64);
	col = 1 + (3 * (pos % 64));
	color_pair = PAIR_NUMBER(mvwinch(matrix, row, col) & A_COLOR);
	if (color_pair >= 3 && color_pair <= 6)
		mvwchgat(matrix, row, col, 2, A_COLOR, color_pair + 4, NULL);
	else if (color_pair == 2)
		mvwchgat(matrix, row, col, 2, A_COLOR, 11, NULL);
	wrefresh(matrix);
}

void	unset_cursor_color(WINDOW *matrix, int proc_id, unsigned int pos)
{
	unsigned int	row;
	unsigned int	col;
	short			color_pair;

	row = 1 + (pos / 64);
	col = 1 + (3 * (pos % 64));
	color_pair = PAIR_NUMBER(mvwinch(matrix, row, col) & A_COLOR);
	if (color_pair >= 7 && color_pair <= 10)
		mvwchgat(matrix, row, col, 2, A_COLOR, color_pair - 4, NULL);
	else if (color_pair == 11)
		mvwchgat(matrix, row, col, 2, A_COLOR, 2, NULL);
	wrefresh(matrix);
}
/*
 * threads ???????????

void	*thread_hl_live(void *data)
{
	t_vm	*vm;
	WINDOW	*matrix;
	int		proc_id;
	int		proc_pc;
	int		pos;
	short	color_pair;
	short	og_color;
	int		row;
	int		col;
	int		cycle_end;


	vm = ((t_thdata*)(data))->vm;
	matrix = ((t_thdata*)(data))->vm->win->matrix;
	proc_id = ((t_thdata*)(data))->proc_id;
	proc_pc = ((t_thdata*)(data))->proc_pc;

	pos = proc_pc % MEM_SIZE; 
	row = 1 + (pos / 64);
	col = 1 + (3 * (pos % 64));

	color_pair = (-proc_id - 1) + 12;
	og_color = PAIR_NUMBER(mvwinch(matrix, row, col) & A_COLOR);

	mvwchgat(matrix, row, col, 2,
			A_COLOR, color_pair, NULL);
	wrefresh(matrix);
	cycle_end = vm->cycle + 50;
	while (1)
	{
		if (vm->cycle == cycle_end)
		{
			mvwchgat(matrix, row, col, 2,
					A_COLOR, COLOR_PAIR(og_color), NULL);
			wrefresh(matrix);
			break ;
		}
	}
	free(data);
	pthread_exit(NULL);
}

void	highlight_live(t_vm *vm, t_proc *proc)
{
	t_thdata	*data;
	pthread_t	thread_hll;

	if (!(data = ft_memalloc(sizeof(t_thdata))))
		exit(EXIT_FAILURE);
	data->vm = vm;
	data->proc_id = proc->id;
	data->proc_pc = proc->pc;
	pthread_create(&thread_hll, NULL, thread_hl_live, (void*)data);
}
*/
void	update_visu(t_vm *vm, char ch)
{
	if (ch == ' ')
		while ((ch = getch()) != ' ')
			;
	usleep(10000);
}
