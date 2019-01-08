#include "op.h"

int		launch_proc(t_proc *proc, t_vm *vm, int procnb)
{
	static int	(*f[17])(t_proc *proc, t_vm *vm) = {0,
		ft_live, ft_ld, ft_st, ft_add, ft_sub, ft_and, ft_or, ft_xor, ft_zjmp,
		ft_ldi, ft_sti, ft_fork, ft_lld, ft_lldi, ft_lfork, ft_aff};
	int			i;
	static int	opc[4] = {0, 1, 0, 2};
	t_opmodvm	*optab;

	i = 0;
	optab = get_op_tab_vm();
	opc[2] = optab[proc->type].dirsize;
	if (proc->size == 1)
		return (-1);
	if (optab[proc->type].ocp && (proc->opcode < 64 || proc->opcode > 255 || !check_ocp(proc)))
	{
		proc->opcode = (proc->opcode >> (8 - (2 * optab[proc->type].paramnb))) <<
			(8 - (2 * optab[proc->type].paramnb));
		proc->size = opc[(proc->opcode & 0xC0) >> 6] + opc[(proc->opcode & 0x30) >> 4]
			+ opc[(proc->opcode & 0xC) >> 2] + 2;
		return (-1);
	}
	else if (!proc->size)
		proc->size = calc_size(proc);
	while (i < proc->paramnb)
	{
		if (proc->paramtype[i] == T_REG && (proc->paramval[i] < 0 || proc->paramval[i] > 15))
		{
			proc->opcode = (proc->opcode >> (8 - (2 * optab[proc->type].paramnb))) <<
				(8 - (2 * optab[proc->type].paramnb));
			proc->size = (opc[(proc->opcode & 0xC0) >> 6] + opc[(proc->opcode & 0x30) >> 4]
				+ opc[(proc->opcode & 0xC) >> 2] + 2);
			return (-1);
		}
		i++;
	}
	if ((vm->verbose & 4) == 4 && proc->size != 1)
		ft_printf("\nP%*d | ", ft_nblen(procnb) < 5 ? 5 : ft_nblen(procnb) + 1, procnb);
	return (f[proc->type](proc, vm));
}
