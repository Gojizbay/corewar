/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_toupper.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:50:05 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/02 17:28:59 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strtoupper(char *s)
{
	int		i;
	int		j;
	char	*d;

	i = 0;
	j = pf_strlen(s);
	if (!(d = (char*)malloc(sizeof(char) * (j + 1))))
		return (NULL);
	while (s[i])
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			d[i] = s[i] - 32;
		else
			d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	ft_strdel(&s);
	return (d);
}

int		ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
