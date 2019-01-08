/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:45:05 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/14 17:45:07 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f) (char))
{
	int		i;
	int		len;
	char	*d;

	d = NULL;
	i = 0;
	if (s)
	{
		len = ft_strlen(s);
		if (s[i])
		{
			d = (char*)malloc(sizeof(char) * (len + 1));
			if (d)
			{
				d[len] = '\0';
				while (i < len && s[i])
				{
					d[i] = f(s[i]);
					i++;
				}
			}
		}
	}
	return (d);
}
