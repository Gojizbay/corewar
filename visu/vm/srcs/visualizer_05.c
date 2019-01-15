/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   visualizer_05.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 17:42:12 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 19:30:33 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

void	compute_live_breakdown(t_champ *champ)
{
	t_champ		*node;

	node = champ;
	while (champ)
	{

		champ = champ->next;
	}
}


/*
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

	pthread_mutex_lock(&g_mutex);
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
	pthread_mutex_unlock(&g_mutex);
	cycle_end = vm->cycle + 50;
	while (1)
	{
		if (vm->cycle == cycle_end)
		{
			pthread_mutex_lock(&g_mutex);
			mvwchgat(matrix, row, col, 2,
					A_COLOR, COLOR_PAIR(og_color), NULL);
			wrefresh(matrix);
			pthread_mutex_unlock(&g_mutex);
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
