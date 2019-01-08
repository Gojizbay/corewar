#include "op.h"

t_vm	*init_vm(void)
{
	t_vm	*vm;

	if (!(vm = ft_memalloc(sizeof(t_vm))))
		return (NULL);
	vm->ctd = CYCLE_TO_DIE;
	if (!(vm->champ = init_champ()))
		return (NULL);
	vm->dump = -1;
	return (vm);
}

int			free_all(t_vm *vm)
{
	t_cycles	*tmp;
	t_champ		*tmpchamp;

	while (vm->proclist)
	{
		tmp = vm->proclist->next;
		free(vm->proclist);
		vm->proclist = tmp;
	}
	while (vm->champ)
	{
		tmpchamp = vm->champ->next;
		if (vm->champ->head)
			free(vm->champ->head);
		free(vm->champ);
		vm->champ = tmpchamp;
	}
	free(vm);
	return (0);
}

t_cycles		*init_cycles(t_cycles *prev)
{
	t_cycles	*cycles;
	int			i;

	i = 0;
	if (!(cycles = ft_memalloc(sizeof(t_cycles))))
		return (NULL);
	cycles->prev = prev;
	return (cycles);
}

void			first_cycle(t_vm *vm)
{
	int			i;
	int			j;
	t_champ		*champs;

	i = 0;
	j = -1;
	if (!vm->champ_nb || !(vm->proclist = init_cycles(NULL)))
		return ;
	while (-j <= vm->champ_nb)
	{
		champs = vm->champ;
		while (champs)
		{
			if (champs->id == j)
			{
				if (!(vm->proclist->proc[i] = init_proc()))
					return ;
				vm->proclist->proclen++;
				vm->procnb++;
				fill_proc(vm->proclist->proc[i++], vm, champs->id, champs->mempos);
				break ;
			}
			champs = champs->next;
		}
		j--;
	}
	vm->cycle++;
}
