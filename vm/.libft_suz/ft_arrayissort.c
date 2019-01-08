/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:43:19 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/15 14:18:41 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_arrayissort(int *tab, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size - 2 && tab[i] == tab[i + 1])
		i++;
	if (i < size - 2 && tab[i] < tab[i + 1])
	{
		while (i < size - 2 && tab[i] <= tab[i + 1])
		{
			if (tab[i] <= tab[i + 1])
				i++;
		}
		if (i == size - 2 && tab[i] <= tab[i + 1])
			return (1);
	}
	return (0);
}
