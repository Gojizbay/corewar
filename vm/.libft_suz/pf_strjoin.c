/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:44:33 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 10:40:34 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pf_strjoin(char *s1, char *s2)
{
	char	*d;
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (!s1 || !s2)
		return (NULL);
	if (s1[0] == '\0' && s2[0] == '\0')
		j = 0;
	d = (char*)malloc(sizeof(char *) * (pf_strlen(s1) + pf_strlen(s2) - j + 1));
	if (d == 0)
		return (NULL);
	if (s1 && s2)
	{
		ft_strcpy(d, s1);
		ft_strcat(d, s2);
	}
	ft_strdel(&s1);
	return (d);
}
