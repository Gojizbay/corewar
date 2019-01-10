/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:49:09 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/15 17:38:20 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		*ft_arraysub(int *tab, unsigned int start, size_t len)
{
	size_t	i;
	int		*tronc;

	i = 0;
	if (!(tronc = (int*)malloc(sizeof(int) * len)))
		return (0);
	if (tab && len)
	{
		while (i < len)
			tronc[i++] = tab[start++];
		return (tronc);
	}
	return (tronc);
}
