/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   median.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/26 17:38:44 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/15 14:17:59 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_median(int *tab, int len)
{
	int		i;
	int		j;
	int		sup;
	int		min;

	j = 1;
	while (j < len)
	{
		min = 0;
		sup = 0;
		i = 0;
		while (i < len)
		{
			if (i != j && tab[i] <= tab[j])
				min++;
			if (i != j && tab[i] >= tab[j])
				sup++;
			i++;
		}
		if (min == sup || min - sup == 1 || sup - min == 1)
			return (j);
		j++;
	}
	return (0);
}
