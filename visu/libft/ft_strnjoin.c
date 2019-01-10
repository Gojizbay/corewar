/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnjoin.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:47:49 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/14 17:47:51 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
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
	if (ft_strlen(s2) > n)
		d = (char*)malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2) - j));
	else
		d = (char*)malloc(sizeof(char *) * (ft_strlen(s1) + n + 1));
	if (d == 0)
		return (NULL);
	if (s1 && s2)
	{
		ft_strcpy(d, s1);
		ft_strncat(d, s2, n);
	}
	return (d);
}
