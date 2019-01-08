/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ope3.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/19 15:54:12 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/18 14:36:07 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		ft_sti(t_proc *proc, t_vm *vm)
{
	int			val1;
	int			val2;
	int			j;

	val1 = 0;
	val2 = 0;
	if (proc->paramtype[1] == T_DIR)
		val1 = proc->paramval[1];
	else if (proc->paramtype[1] == T_IND)
		val1 = read_mem(vm->mem, proc->pc + (proc->paramval[1] % IDX_MOD),
				REG_SIZE);
	else if (proc->paramtype[1] == T_REG)
		val1 = proc->regs[proc->paramval[1]];
	if (proc->paramtype[2] == T_DIR)
		val2 = proc->paramval[2];
	else if (proc->paramtype[2] == T_REG)
		val2 = proc->regs[proc->paramval[2]];
	j = val1 + val2;
	if ((vm->verbose & 4) == 4)
	{
		ft_printf("sti r%d %d %d", proc->paramval[0] + 1, val1, val2);
		ft_printf("\n       | -> store to %d + %d = %d (with pc and mod %d)",
				val1, val2, j, proc->pc + j % IDX_MOD);
	}
	write_mem(vm->mem, proc->pc + j % IDX_MOD + REG_SIZE - 1, REG_SIZE,
			proc->regs[proc->paramval[0]]);
	return (1);
}

int		update_proclist(t_proc *proc, t_cycles *proclist)
{
	while (proclist->next)
		proclist = proclist->next;
	if (proclist->proclen == PROC_NB)
	{
		if (!(proclist->next = init_cycles(proclist)))
			return (0);
		proclist = proclist->next;
		proclist->i = proclist->prev->i + 1;
	}
	proclist->proc[proclist->proclen] = proc;
	proclist->proclen++;
	return (1);
}

int		ft_fork(t_proc *proc, t_vm *vm)
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
	son->pc = (MEM_SIZE + (proc->pc + (proc->paramval[0] % IDX_MOD))) % MEM_SIZE;
	son->type = vm->mem[son->pc];
	if ((vm->verbose & 4) == 4)
		ft_printf("fork %d (%d)", proc->paramval[0], proc->pc + proc->paramval[0] % IDX_MOD);
	son->carry = proc->carry;
	son->lastlive = proc->lastlive;
	son->lives = 0;
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

int		ft_lld(t_proc *proc, t_vm *vm)
{
	int		val1;

	if (!check_ocp(proc))
		return (0);
	if ((vm->verbose & 4) == 4)
		ft_printf("lld %d r%d", proc->paramval[0], proc->paramval[1] + 1, proc->opcode);
	val1 = 0;
	proc->carry = !proc->regs[proc->paramval[1]] ? 1 : 0;
	if (proc->paramtype[0] == T_IND)
		val1 = read_mem(vm->mem, proc->pc + proc->paramval[0], REG_SIZE);
	else if (proc->paramtype[0] == T_DIR)
		val1 = proc->paramval[0];
	proc->regs[proc->paramval[1]] = val1;
	return (0);
}

int		ft_lldi(t_proc *proc, t_vm *vm)
{
	int			val1;
	int			val2;
	int			sum;

	if ((vm->verbose & 4) == 4)
		ft_printf("lldi %d %d r%d", proc->paramtype[0] == T_REG ? proc->regs[proc->paramval[0]] : proc->paramval[0], proc->paramtype[1] == T_REG ? proc->regs[proc->paramval[1]] : proc->paramval[1], proc->paramval[2] + 1);
	if (!check_ocp(proc))
		return (0);
	val1 = 0;
	val2 = 0;
	if (proc->paramtype[0] == T_DIR)
		val1 = proc->paramval[0];
	else if (proc->paramtype[0] == T_IND)
		val1 = read_mem(vm->mem, proc->pc + proc->paramval[0], IND_SIZE);
	else if (proc->paramtype[0] == T_REG)
		val2 = proc->regs[proc->paramval[0]];
	if (proc->paramtype[1] == T_DIR)
		val2 = proc->paramval[1];
	else if (proc->paramtype[1] == T_REG)
		val2 = proc->regs[proc->paramval[1]];
	sum = (val1 + val2) % MEM_SIZE;
	if ((vm->verbose & 4) == 4)
		ft_printf("\n       | -> load from %d + %d = %d (with pc and mod %d)",
				val1, val2, sum, proc->pc + sum);
	proc->regs[proc->paramval[2]] = read_mem(vm->mem, proc->pc + sum, REG_SIZE);
	proc->carry = !proc->regs[proc->paramval[2]] ? 1 : 0;
	return (0);
}
