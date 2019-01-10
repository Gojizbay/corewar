/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_options.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/18 17:41:33 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/18 20:02:02 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

static int	get_dump(t_vm *vm, int dump)
{
	vm->dump = dump;
	vm->vis = vm->vis ? -1 : 0;
	return (2);
}

static int	get_beautiful_visu(t_vm *vm)
{
	vm->vis = vm->dump ? -1 : 1;
	return (1);
}

static int	get_aff(t_vm *vm)
{
	vm->aff = 1;
	return (1);
}

static int	get_verbose(t_vm *vm, int verb)
{
	vm->verbose = verb;
	return (2);
}

int			options(int ac, char **av, t_vm *vm)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (ac - i > 1 && !ft_strcmp(av[i], "-d"))
			i += get_dump(vm, ft_atoi(av[i + 1]));
		else if (ac - 1 > 0 && !ft_strcmp(av[i], "-b"))
			i += get_beautiful_visu(vm);
		else if (ac > 0 && !ft_strcmp(av[i], "-a"))
			i += get_aff(vm);
		else if (ac > 1 && !ft_strcmp(av[i], "-v"))
			i += get_verbose(vm, ft_atoi(av[i + 1]));
		else
			return (i);
	}
	return (i);
}
