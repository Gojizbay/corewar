/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrchr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:48:08 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/14 17:48:10 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	a;

	i = ft_strlen(s);
	a = c;
	while (i != 0 && s[i] != a)
		i--;
	if (i == 0 && s[i] == a)
		return ((char*)s);
	if (i != 0 || a == '\0')
		return ((char*)(s + i));
	return (NULL);
}
