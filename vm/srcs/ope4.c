/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ope1.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/17 11:11:26 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/14 17:43:37 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		check_ocp(t_proc *proc)
{
	int			i;
	t_opmodvm	*optab;

	i = 0;
	optab = get_op_tab_vm();
	if (proc->opcode < 64)
		return (0);
	while (i < proc->paramnb)
	{
		if (proc->paramtype[i] == 0 || (proc->paramtype[i]
					& optab[proc->type].paramtype[i]) != proc->paramtype[i])
			return (0);
		i++;
	}
	return (1);
}

int		ft_lfork(t_proc *proc, t_vm *vm)
{
	t_proc		*son;
	int			i;
	t_opmodvm	*optab;

	vm->procnb++;
	optab = get_op_tab_vm();
	i = 0;
	if (!(son = init_proc()))
		return (0);
	if (!(update_proclist(son, vm->proclist)))
		return (0);
	while (i < REG_NUMBER - 1)
	{
		son->regs[i] = proc->regs[i];
		i++;
	}
	son->pc = (MEM_SIZE + (proc->pc + proc->paramval[0])) % MEM_SIZE;
	son->type = vm->mem[son->pc];
	son->lastlive = proc->lastlive;
	son->carry = proc->carry;
	if ((vm->verbose & 4) == 4)
		ft_printf("lfork %d (%d)", proc->paramval[0], proc->pc +  proc->paramval[0]);
	if (son->type < 1 || son->type > 16)
	{
		son->cycles_exec = vm->cycle + 1;
		son->size = 1;
		return (0);
	}
	son->cycles_exec = vm->cycle + optab[son->type].cycles;
	son->size = 0;
	return (1);
}

int		ft_aff(t_proc *proc, t_vm *vm)
{
	char	c;

	if ((vm->verbose & 4) == 4)
		ft_printf("aff r%d", proc->paramval[0] + 1);
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
