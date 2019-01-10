/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:39:25 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/14 17:39:27 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*u;

	u = NULL;
	if (len)
	{
		i = 0;
		u = (unsigned char *)b;
		while (i < len)
		{
			u[i] = (unsigned char)c;
			i++;
		}
	}
	return (b);
}
