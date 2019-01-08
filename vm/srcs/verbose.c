/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   verbose.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/18 20:38:00 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/18 20:59:01 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

void	verb_proc_lives(t_vm *vm, t_cycles *start, int i)
{
	if ((vm->verbose & 8) == 8)
		ft_printf("\nProcess %d hasn't lived for %d cycles (CTD %d)",
			i + start->i * PROC_NB + 1, vm->cycle - start->proc[i]->lastlive,
			vm->ctd);
}

void	verb_cycle(t_vm *vm, int mode)
{
	if ((vm->verbose & 2) == 2)
	{
		if (mode == 1)
			ft_printf("\nIt is now cycle %d", vm->cycle);
		else if (mode == 2)
			ft_printf("\nCycle to die is now %d", vm->ctd);
	}
}
