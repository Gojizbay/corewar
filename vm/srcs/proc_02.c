/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   proc_tools.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/30 18:07:10 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/14 17:40:44 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

void			free_proc(t_proc **proc, t_vm *vm)
{
	free(*proc);
	*proc = NULL;
	vm->procnb--;
}

int				find_next_exec_cycle(t_proc *proc, t_vm *vm)
{
	t_opmodvm	*optab;

	optab = get_op_tab_vm();
	proc->pc = (proc->pc + proc->size) % MEM_SIZE;
	proc->type = vm->mem[proc->pc];
	if (proc->type < 1 || proc->type > 16)
	{
		proc->cycles_exec = vm->cycle;
		proc->size = 1;
		return (0);
	}
	proc->size = 0;
	proc->cycles_exec = vm->cycle + optab[proc->type].cycles - 1;
	return (1);
}

int				check_proc_to_exec(t_vm *vm)
{
	int			i;
	int			ret;
	t_cycles	*cycles;

	ret = 0;
	cycles = vm->proclist;
	while (cycles->next)
		cycles = cycles->next;
	while (cycles)
	{
		i = cycles->proclen - 1;
		while (i >= 0)
		{
			if (cycles->proc[i] && cycles->proc[i]->cycles_exec == vm->cycle - 1)
				find_next_exec_cycle(cycles->proc[i], vm);
			if (cycles->proc[i] && cycles->proc[i]->cycles_exec == vm->cycle)
			{
				exec_proc(cycles->proc[i], vm, cycles->i * PROC_NB + i + 1);
				ret = 1;
			}
			i--;
		}
		cycles = cycles->prev;
	}
	return (ret);
}

int				exec_proc(t_proc *proc, t_vm *vm, int procnb)
{
	int			i;

	i = 0;
	if (!proc->size)
		refill_proc(proc, vm);
	launch_proc(proc, vm, procnb);
	if ((vm->verbose & 16) == 16 && (proc->type != 9 || !proc->carry)
			&& proc->size != 1)
	{
		ft_printf("\nADV %d (0x%.4x -> 0x%.4x) ", proc->size, proc->pc,
				proc->pc + proc->size);
		while (i < proc->size)
		{
			ft_printf("%.2x ", vm->mem[(proc->pc + i) % MEM_SIZE]);
			i++;
		}
	}
	return (1);
}

int				ctd_vs_lives(t_proc *proc, t_vm *vm)
{
	return (vm->cycle - proc->lastlive >= vm->ctd);
}

int				check_proc_lives(t_vm *vm)
{
	t_cycles	*start;
	int			i;
	int			ret;

	ret = 1;
	start = vm->proclist;
	while (start->next)
		start = start->next;
	while (start)
	{
		i = start->proclen/* - 1*/;
		while (--i >= 0)
		{
			if (start->proc[i] && ctd_vs_lives(start->proc[i], vm))
			{
				verb_proc_lives(vm, start, i);
				free_proc(&start->proc[i], vm);
			}
		//	i--;
		}
		start = start->prev;
	}
	if (vm->lives >= NBR_LIVE)
		ret = 0;
	return (ret);
}
