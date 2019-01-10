/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ope4.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/10 18:26:05 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 18:57:54 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

int		check_ocp(t_proc *proc)
{
	int			i;
	t_opmodvm	*optab;

	i = 0;
	optab = get_op_tab_vm();
	if (proc->ocp < 64)
		return (0);
	while (i < proc->paramnb)
	{
		if (proc->paramtype[i] == 0 || (proc->paramtype[i]
				& optab[(int)proc->type].paramtype[i]) != proc->paramtype[i])
			return (0);
		i++;
	}
	return (1);
}

void	fill_son(t_proc *son, t_proc *proc, t_vm *vm, int pc)
{
	t_opmodvm	*optab;
	int			i;

	i = 0;
	optab = get_op_tab_vm();
	while (i < REG_NUMBER - 1)
	{
		son->regs[i] = proc->regs[i];
		i++;
	}
	son->id = proc->id;
	son->pc = (MEM_SIZE + pc)
		% MEM_SIZE;
	son->type = vm->mem[son->pc];
	son->carry = proc->carry;
	son->lastlive = proc->lastlive;
	son->lives = 0;
	if (son->type < 1 || son->type > 16)
	{
		son->cycles_exec = vm->cycle + 1;
		son->size = 1;
		return ;
	}
	son->cycles_exec = vm->cycle + optab[(int)son->type].cycles;
	son->size = 0;
}

int		update_proclist(t_proc *proc, t_proctab *proclist)
{
	while (proclist->next)
		proclist = proclist->next;
	if (proclist->proclen == PROC_NB)
	{
		if (!(proclist->next = init_proctab(proclist)))
			return (0);
		proclist = proclist->next;
		proclist->i = proclist->prev->i + 1;
	}
	proclist->proc[proclist->proclen] = proc;
	proclist->proclen++;
	return (1);
}

int		ft_lfork(t_proc *proc, t_vm *vm)
{
	t_proc		*son;
	int			i;
	int			pc;

	vm->procnb++;
	i = 0;
	if (!(son = init_proc()))
		return (0);
	if (!(update_proclist(son, vm->proclist)))
		return (0);
	pc = proc->pc + proc->paramval[0];
	verbose_ope(proc->paramval[0], pc, proc, vm);
	fill_son(son, proc, vm, pc);
	return (1);
}

int		ft_aff(t_proc *proc, t_vm *vm)
{
	char	c;

	verbose_ope(0, 0, proc, vm);
	if (vm->aff)
	{
		c = proc->paramval[0] % 256;
		if (!check_ocp(proc))
			return (0);
		write(1, "Aff: ", 5);
		write(1, &c, 1);
		write(1, "\n", 1);
	}
	else
		ft_printf("aff ");
	return (1);
}
