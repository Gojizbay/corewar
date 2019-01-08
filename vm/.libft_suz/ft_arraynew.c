/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:47:34 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/15 17:41:17 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		*ft_arraynew(size_t size)
{
	int		*tab;
	size_t	i;

	i = 0;
	tab = (int*)malloc(sizeof(int) * size + 1);
	if (tab)
	{
		while (i < size)
		{
			tab[i] = 0;
			i++;
		}
		return (tab);
	}
	return (0);
}
