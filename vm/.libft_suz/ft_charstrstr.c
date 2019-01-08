/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_charstrstr.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/07 14:28:06 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/09 12:57:59 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_charstrstr(const char *s1, const char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] != s2[j] && s1[i] != '\0')
	{
		j = 0;
		while (s1[i] != s2[j] && s2[j] != '\0')
			j++;
		if (s1[i] == s2[j])
			return (i);
		i++;
	}
	if (s1[i] == s2[j])
		return (i);
	return (0);
}
