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

#include "op.h"

void		set_dump(int cycle)
{
	g_arg.flags |= DUMP;
	g_arg.dump_cycle = cycle;
}

void		set_verbose(int level)
{
	g_arg.flags |= VERB;
	g_arg.verb_lvl |= level;
}

void		check_players_id(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < MAX_PLAYERS - 1)
	{
		j = i + 1;
		if (g_arg.player_id[i] > 0)
			g_arg.player_id[i] = -g_arg.player_id[i];
		while (j < MAX_PLAYERS)
		{
			if (g_arg.player_id[i] == g_arg.player_id[j])
				ft_error("wrong number assignment with -n");
			j++;
		}
		i++;
	}
	if (g_arg.player_id[i] > 0)
			g_arg.player_id[i] = -g_arg.player_id[i];
}

void		get_arg(int ac, char *av[], t_vm *vm)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!ft_strcmp("-d", av[i]) && i + 1 < ac)
			set_dump(ft_atoi(av[++i]));
		else if (!ft_strcmp("-v", av[i]) && i + 1 < ac)
			set_verbose(ft_atoi(av[++i]));
		else if (!ft_strcmp("-a", av[i]))
			g_arg.flags |= AFF;
		else if (!ft_strcmp("-b", av[i]))
			g_arg.flags |= VISU;
		else if (!ft_strcmp("-n", av[i]))
			g_arg.player_id[vm->champ_nb] = ft_atoi(av[++i]);
		else
		{
			if (vm->champ_nb < MAX_PLAYERS)
				g_arg.file[vm->champ_nb++] = av[i];
			else
				ft_error("Too many players");
		}
		i++;
	}
	check_players_id();
}
