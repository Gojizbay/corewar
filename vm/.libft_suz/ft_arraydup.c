/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:43:48 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/15 17:33:36 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		*ft_arraydup(int *tab1, size_t size)
{
	int		*tab2;
	size_t	i;

	tab2 = (int*)malloc(sizeof(int) * size + 1);
	if (!tab2)
		return (NULL);
	i = 0;
	while (i < size)
	{
		tab2[i] = tab1[i];
		i++;
	}
	return (tab2);
}
