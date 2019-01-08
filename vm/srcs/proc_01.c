#include "op.h"

t_proc			*init_proc(void)
{
	t_proc		*proc;

	if (!(proc = malloc(sizeof(t_proc))))
		return (NULL);
	ft_memset(proc->regs, 0, REG_NUMBER - 1);
	proc->type = 0;
	proc->paramnb = 0;
	proc->opcode = 0;
	ft_memset(proc->paramtype, 0, 4);
	ft_memset(proc->paramval, 0, 4);
	proc->cycles_exec = 0;
	proc->pc = 0;
	proc->lives = 0;
	proc->carry = 1;
	proc->size = 0;
	proc->lastlive = 0;
	return (proc);
}

int				fill_proc(t_proc *proc, t_vm *vm, int id, int mempos)
{
	int			i;
	t_opmodvm	*optab;

	i = 0;
	optab = get_op_tab_vm();
	while (i < REG_NUMBER - 1)
		proc->regs[i++] = 0;
	proc->regs[0] = id;
	proc->pc = mempos;
	if ((proc->type = vm->mem[mempos]) < 1 || proc->type > 16)
	{
		proc->lastlive = 1;
		proc->cycles_exec = vm->cycle + 1;
		proc->size = 1;
		return (0);
	}
	proc->opcode = optab[proc->type].ocp ? vm->mem[(proc->pc + 1) % MEM_SIZE] : 0;
	proc->cycles_exec = vm->cycle + optab[proc->type].cycles;
	proc->paramnb = optab[proc->type].paramnb;
	proc->size = calc_size(proc);
	proc->carry = 0;
	proc->lives = 0;
	proc->lastlive = 1;
	fill_paramval(proc, vm);
	return (1);
}

size_t			calc_size(t_proc *proc)
{
	int			size;
	int			i;
	static int	opc[4] = {0, 1, 0, 2};
	static int	opt[4] = {0, T_REG, T_DIR, T_IND};
	t_opmodvm	*optab;

	i = 0;
	optab = get_op_tab_vm();
	opc[2] = optab[proc->type].dirsize;
	if (optab[proc->type].ocp == 0)
	{
		proc->opcode = 0;
		proc->paramtype[0] = T_DIR;
		return (1 + opc[2]);
	}
	size = (opc[(proc->opcode & 0xC0) >> 6] + opc[(proc->opcode & 0x30) >> 4]
		+ opc[(proc->opcode & 0xC) >> 2] + 2);
	while (i < proc->paramnb)
	{
		proc->paramtype[i] = opt[(proc->opcode >> (6 - (2 * i))) & 3];
		i++;
	}
	return (size);
}

int				fill_paramval(t_proc *proc, t_vm *vm)
{
	int			i;
	int			j;
	int			k;
	static int	opc[4] = {0, 1, 0, IND_SIZE};
	t_opmodvm	*optab;

	i = 0;
	optab = get_op_tab_vm();
	j = proc->opcode ? 1 : 0;
	opc[2] = optab[proc->type].dirsize;
	while (i < proc->paramnb)
	{
		proc->paramval[i] = 0;
		if (proc->paramtype[i] == T_REG)
			proc->paramval[i] = read_mem(vm->mem, proc->pc + j + 1, 1) - 1;
		else if (proc->paramtype[i] == T_DIR || proc->paramtype[i] == T_IND)
		{
			k = proc->paramtype[i] == T_DIR ? 2 : 3;
			proc->paramval[i] = manage_nega(proc->paramtype[i], opc[k],
					read_mem(vm->mem, proc->pc + j + opc[k], opc[k]));
		}
		j += opc[(proc->opcode >> (6 - i * 2)) & 0x3];
		i++;
	}
	return (0);
}

int				refill_proc(t_proc *proc, t_vm *vm)
{
	t_opmodvm	*optab;

	optab = get_op_tab_vm();
	proc->opcode = optab[proc->type].ocp ? vm->mem[(proc->pc + 1) % MEM_SIZE]
		: 0;
	proc->paramnb = optab[proc->type].paramnb;
	proc->size = calc_size(proc);
	fill_paramval(proc, vm);
	return (1);
}
