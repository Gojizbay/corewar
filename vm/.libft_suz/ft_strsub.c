/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:49:09 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 17:30:54 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*tronc;

	i = 0;
	if (!(tronc = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (s && len)
	{
		while (i < len)
		{
			tronc[i++] = s[start++];
		}
		tronc[i] = '\0';
		return (tronc);
	}
	return (tronc);
}
