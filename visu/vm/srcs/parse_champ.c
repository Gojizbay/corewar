/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_champ.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 12:58:42 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/13 19:20:17 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

t_header	*init_head(void)
{
	t_header	*head;

	if (!(head = malloc(sizeof(t_header))))
		return (NULL);
	ft_memset(head->prog_name, '\0', PROG_NAME_LENGTH + 1);
	ft_memset(head->comment, '\0', COMMENT_LENGTH + 1);
	head->magic = 0;
	head->prog_size = 0;
	return (head);
}

static t_vm	*init_vm(void)
{
	t_vm		*vm;

	if (!(vm = malloc(sizeof(t_vm))))
		return (NULL);
	vm->champ_nb = 0;
	memset(vm->mem, 0, MEM_SIZE);
	vm->proclist = NULL;
	vm->champ = NULL;
	vm->cycle = 0;
	vm->lives = 0;
	vm->procnb = 0;
	vm->aff = 0;
	vm->verbose = 0;
	vm->ctd = CYCLE_TO_DIE;
	vm->dump = -1;
	vm->n = 0;
	vm->vis = 0;
	vm->check = 0;
	return (vm);
}

int			free_all(t_vm *vm)
{
	t_proctab	*tmp;
	t_champ		*tmpchamp;

	while (vm->proclist)
	{
		tmp = vm->proclist->next;
		free(vm->proclist);
		vm->proclist = tmp;
	}
	while (vm->champ)
	{
		if (vm->champ->head)
			free(vm->champ->head);
		tmpchamp = vm->champ->next;
		free(vm->champ);
		vm->champ = tmpchamp;
	}
	free(vm);
	return (0);
}

int			check_champs_nb(t_vm *vm)
{
	t_champ		*champ;
	int			i;
	int			bol;

	i = 1;
	bol = 0;
	while (i <= vm->champ_nb)
	{
		champ = vm->champ;
		while (champ)
		{
			if (bol == 1 && champ->id == -i)
				return (0);
			if (champ->id == -i)
				bol = 1;
			champ = champ->next;
		}
		bol = 0;
		i++;
	}
	return (1);
}

int			main(int ac, char **av)
{
	int			i;
	t_vm		*vm;

	vm = init_vm();
	i = options(ac, av, vm);
	if (ac > i)
	{
		if (!(vm->champ = init_champ()))
			return (free_all(vm));
	}
	else
		return (print_man(vm));
	if (vm->vis)
		start_visualizer(vm);
	if (get_champs(ac, i, vm, av))
		return (free_all(vm));
/*	if (vm->vis)
	{
		getch();
		nodelay(stdscr, TRUE);
	}*/
	else if (introduce_contestants(vm))
		return (free_all(vm));
	if (launch_vm(vm) == vm->dump && vm->vis == 0 && vm->dump >= 0)
		print_dump(vm);
	else
		print_result(vm);
	if (vm->vis)
		close_windows(vm->win);
	return (free_all(vm));
}
