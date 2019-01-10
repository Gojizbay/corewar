/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   champ_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/18 19:59:21 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 19:27:46 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op_vm.h"

t_champ			*init_champ(void)
{
	t_champ			*champ;

	if (!(champ = malloc(sizeof(t_champ))))
		return (NULL);
	champ->id = 0;
	champ->mempos = 0;
	champ->head = init_head();
	champ->next = NULL;
	champ->lastlive = 0;
	champ->lives = 0;
	return (champ);
}

static t_champ	*read_champ(int fd, t_champ *champ, t_vm *vm)
{
	unsigned char	bf[CHAMP_MAX_SIZE + 16 + COMMENT_LENGTH + PROG_NAME_LENGTH];
	unsigned int	i;
	int				j;
	unsigned int	ret;

	j = 0;
	if ((ret = read(fd, bf, sizeof(bf))) < 16 + COMMENT_LENGTH
			+ PROG_NAME_LENGTH)
		return (NULL);
	if ((champ->head->magic = read_mem(bf, 3, 4)) != MAGIC)
		return (NULL);
	champ->head->prog_size = read_mem(bf, PROG_NAME_LENGTH + 11, 4);
	ft_memcpy(champ->head->prog_name, bf + 4, PROG_NAME_LENGTH);
	champ->head->prog_name[PROG_NAME_LENGTH] = '\0';
	ft_memcpy(champ->head->comment, bf + 12 + PROG_NAME_LENGTH,
			COMMENT_LENGTH);
	champ->head->comment[COMMENT_LENGTH] = '\0';
	i = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	if (ret == PROG_NAME_LENGTH + COMMENT_LENGTH + 16
			+ champ->head->prog_size)
		while (i < ret)
		{
			vm->mem[j++ + champ->mempos] = bf[i++] & 0xff;
			if (vm->vis)
				write_matrix(vm->win->matrix, champ->id,
						j - 1 + champ->mempos, bf[i - 1]);
		}
	else
		return (NULL);
	return (champ);
}

/*
** 16 = taille du magic + taille de la size du prog + deux fois 4
** octets vide, un entre le nom et la size, et un entre le comment et le prog
*/

static t_champ	*fill_champ(int fd, t_champ *champs, t_vm *vm, int ac_minus_i)
{
	champs->mempos = (MEM_SIZE / vm->champ_nb) * (-champs->id - 1);
	if (!(champs = read_champ(fd, champs, vm)))
		return (NULL);
	close(fd);
	if (ac_minus_i > vm->n * 2)
	{
		if (!(champs->next = init_champ()))
			return (NULL);
		champs = champs->next;
	}
	return (champs);
}

static int		get_champs_n(t_vm *vm, int ac, char **av, int i)
{
	int				fd;
	int				nb;
	t_champ			*champs;

	champs = vm->champ;
	vm->champ_nb = vm->champ_nb / 3;
	vm->n = 1;
	while (ac > i)
	{
		if (!ft_strcmp(av[i], "-n") && ac > i + 2 && ft_atoi(av[i + 1]) > 0
				&& (ft_atoi(av[i + 1]) <= vm->champ_nb))
			nb = ft_atoi(av[i + 1]);
		else
			return (ft_printf(N_MESSAGE, MAX_PLAYERS));
		i += 2;
		fd = open(av[i], O_RDONLY);
		champs->id = nb++ * -1;
		if (fd <= 0)
			return (ft_printf(FILE_ERROR, av[i]));
		else if (!(champs = fill_champ(fd, champs, vm, ac - ++i)))
			return (1);
	}
	return (0);
}

int				get_champs(int ac, int i, t_vm *vm, char **av)
{
	int				fd;
	int				nb;
	t_champ			*champs;

	champs = vm->champ;
	vm->champ_nb = ac - i;
	if (!ft_strcmp(av[i], "-n"))
		return (get_champs_n(vm, ac, av, i) ? 1 : 0);
	nb = 1;
	while (ac > i)
	{
		fd = open(av[i], O_RDONLY);
		champs->id = nb++ * -1;
		if (fd <= 0)
			return (ft_printf(FILE_ERROR, av[i]));
		else if (!(champs = fill_champ(fd, champs, vm, ac - ++i)))
			return (champ_error(av[i - 1]));
	}
	return (0);
}
