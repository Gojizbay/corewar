/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:49:32 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 14:50:53 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s)
{
	size_t		j;
	char		*d;
	char		*tmp;

	j = 0;
	tmp = s;
	printf("tmp = %s\n", tmp);
	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	printf("s1 = %s\n", s);
	while (s[j])
		j++;
	while (j && (s[j - 1] == ' ' || s[j - 1] == '\n' ||
			s[j - 1] == '\t'))
		j--;
	if (!j)
		return (s);
	printf("s2 = %s\n", s);
	d = ft_strsub(s, 0, j);
	ft_strncpy(d, s, j);
	printf("d = %s\n", d);
	ft_strdel(&tmp);
	return (d);
}
