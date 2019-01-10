/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_champ.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/20 17:56:35 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 19:27:37 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

t_proctab		*init_proctab(t_proctab *prev)
{
	t_proctab	*proctab;
	int			i;

	i = 0;
	if (!(proctab = malloc(sizeof(t_proctab))))
		return (NULL);
	while (i < PROC_NB)
		proctab->proc[i++] = NULL;
	proctab->proclen = 0;
	proctab->i = 0;
	proctab->next = NULL;
	proctab->prev = prev;
	return (proctab);
}

void			reinit_champlives(t_vm *vm)
{
	t_champ		*champ;

	champ = vm->champ;
	while (champ)
	{
		champ->lives = 0;
		champ = champ->next;
	}
	vm->check = 0;
	vm->ctd -= CYCLE_DELTA;
	verb_cycle(vm, 2);
}

static int		regular_cycle(t_vm *vm, int j)
{
	if (vm->cycle >= (vm->ctd + j))
	{
		j = vm->cycle;
		if (!(check_proc_lives(vm)) || vm->check == MAX_CHECKS - 1)
			reinit_champlives(vm);
		else
			vm->check++;
		if (vm->procnb == 0)
			return (vm->cycle);
		vm->lives = 0;
	}
	return (j);
}

static void		first_cycle(t_vm *vm, int i, int j)
{
	t_champ		*champs;

	if (!vm->champ_nb || !(vm->proclist = init_proctab(NULL)))
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
				fill_proc(vm->proclist->proc[i++], vm, champs->id,
						champs->mempos);
				break ;
			}
			champs = champs->next;
		}
		j--;
	}
	vm->cycle++;
}

int				launch_vm(t_vm *vm)
{
	int			j;

	j = 0;
	first_cycle(vm, 0, -1);
	if (!vm->dump)
		return (vm->cycle);
	while (vm->procnb > 0)
	{
		verb_cycle(vm, 1);
		check_proc_to_exec(vm);
		j = regular_cycle(vm, j);
		if (vm->cycle == vm->dump && vm->vis == -1)
		{
			vm->dump = -1;
			vm->vis = 1;
		}
		else if (vm->cycle == vm->dump)
			return (vm->cycle);
		vm->cycle++;
		if (vm->vis)
			update_visu(vm);
	}
	return (vm->cycle);
}
