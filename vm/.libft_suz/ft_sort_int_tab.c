/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sort_int_tab.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:41:57 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/14 17:41:59 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		*ft_sort_int_tab(int *tab, size_t len)
{
	size_t	i;
	int		j;
	size_t	k;

	k = 1;
	while (k < len)
	{
		i = 0;
		while (i < len - 1)
		{
			if (tab[i] > tab[i + 1])
			{
				j = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = j;
			}
			i++;
		}
		k++;
	}
	return (tab);
}
