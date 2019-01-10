/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ope1.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/17 11:11:26 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/22 17:36:31 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

int		ft_and(t_proc *proc, t_vm *vm)
{
	int			val1;
	int			val2;

	val1 = 0;
	val2 = 0;
	if (proc->paramtype[0] == T_DIR)
		val1 = proc->paramval[0];
	else if (proc->paramtype[0] == T_IND)
		val1 = vm->mem[(proc->pc + (proc->paramval[0] % IDX_MOD)) % MEM_SIZE];
	else if (proc->paramtype[0] == T_REG)
		val1 = proc->regs[proc->paramval[0]];
	if (proc->paramtype[1] == T_DIR)
		val2 = proc->paramval[1];
	else if (proc->paramtype[1] == T_IND)
		val2 = vm->mem[(proc->pc + (proc->paramval[1] % IDX_MOD)) % MEM_SIZE];
	else if (proc->paramtype[1] == T_REG)
		val2 = proc->regs[proc->paramval[1]];
	verbose_ope(val1, val2, proc, vm);
	proc->regs[proc->paramval[2]] = val1 & val2;
	proc->carry = !proc->regs[proc->paramval[2]] ? 1 : 0;
	return (0);
}

int		ft_or(t_proc *proc, t_vm *vm)
{
	int			val1;
	int			val2;

	val1 = 0;
	val2 = 0;
	if (proc->paramtype[0] == T_DIR)
		val1 = proc->paramval[0];
	else if (proc->paramtype[0] == T_IND)
		val1 = vm->mem[(proc->pc + (proc->paramval[0] % IDX_MOD)) % MEM_SIZE];
	else if (proc->paramtype[0] == T_REG)
		val1 = proc->regs[proc->paramval[0]];
	if (proc->paramtype[1] == T_DIR)
		val2 = proc->paramval[1];
	else if (proc->paramtype[1] == T_IND)
		val2 = vm->mem[(proc->pc + (proc->paramval[1] % IDX_MOD)) % MEM_SIZE];
	else if (proc->paramtype[1] == T_REG)
		val2 = proc->regs[proc->paramval[1]];
	verbose_ope(val1, val2, proc, vm);
	proc->regs[proc->paramval[2]] = val1 | val2;
	proc->carry = !proc->regs[proc->paramval[2]] ? 1 : 0;
	return (0);
}

int		ft_xor(t_proc *proc, t_vm *vm)
{
	int			val1;
	int			val2;

	val1 = 0;
	val2 = 0;
	if (proc->paramtype[0] == T_DIR)
		val1 = proc->paramval[0];
	else if (proc->paramtype[0] == T_IND)
		val1 = vm->mem[(proc->pc + (proc->paramval[0] % IDX_MOD)) % MEM_SIZE];
	else if (proc->paramtype[0] == T_REG)
		val1 = proc->regs[proc->paramval[0]];
	if (proc->paramtype[1] == T_DIR)
		val2 = proc->paramval[1];
	else if (proc->paramtype[1] == T_IND)
		val2 = vm->mem[(proc->pc + (proc->paramval[1] % IDX_MOD)) % MEM_SIZE];
	else if (proc->paramtype[1] == T_REG)
		val2 = proc->regs[proc->paramval[1]];
	verbose_ope(val1, val2, proc, vm);
	proc->regs[proc->paramval[2]] = val1 ^ val2;
	proc->carry = !proc->regs[proc->paramval[2]] ? 1 : 0;
	return (0);
}

int		ft_zjmp(t_proc *proc, t_vm *vm)
{
	int			val;

	verbose_ope(proc->paramval[0], proc->carry, proc, vm);
	if (proc->carry == 1)
	{
		val = proc->paramval[0] % IDX_MOD;
		proc->pc = (MEM_SIZE + (proc->pc + val)) % MEM_SIZE;
		proc->size = 0;
		return (1);
	}
	proc->size = 3;
	return (1);
}

int		ft_ldi(t_proc *proc, t_vm *vm)
{
	int			val1;
	int			val2;

	val1 = 0;
	val2 = 0;
	if (proc->paramtype[0] == T_DIR)
		val1 = proc->paramval[0];
	else if (proc->paramtype[0] == T_IND)
		val1 = read_mem(vm->mem, proc->pc + proc->paramval[0] % IDX_MOD,
				IND_SIZE);
	else if (proc->paramtype[0] == T_REG)
		val1 = proc->regs[proc->paramval[0]];
	if (proc->paramtype[1] == T_DIR)
		val2 = proc->paramval[1];
	else if (proc->paramtype[1] == T_REG)
		val2 = proc->regs[proc->paramval[1]];
	verbose_ope(val1, val2, proc, vm);
	proc->regs[proc->paramval[2]] = read_mem(vm->mem, proc->pc +
			(val1 + val2 + REG_SIZE - 1) % IDX_MOD, REG_SIZE);
	return (1);
}
