#include "op.h"

int				launch_vm(t_vm *vm)
{
	int			j;

	j = 0;
	first_cycle(vm);
	if (!vm->dump)
		return (vm->cycle);
	while (vm->procnb > 0)
	{
		verb_cycle(vm, 1);
/*		if (vm->vis == 1)
			beautiful_visualizer(vm);*/
		check_proc_to_exec(vm);
		if (vm->cycle >= (vm->ctd + j))
		{
			j = vm->cycle;
			if (!(check_proc_lives(vm)) || vm->check == MAX_CHECKS - 1)
			{
				vm->check = 0;
				reinit_champlives(vm->champ);
				vm->ctd = vm->ctd - CYCLE_DELTA;
				verb_cycle(vm, 2);
			}
			else
				vm->check++;
			if (vm->procnb == 0)
				return (vm->cycle);
			vm->lives = 0;
		}
		if (vm->cycle == vm->dump)
		{
			if (vm->vis == -1)
			{
				vm->dump = -1;
				vm->vis = 1;
			}
			else
				return (vm->cycle);
		}
		vm->cycle++;
	}
	return (vm->cycle);
}
