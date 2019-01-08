/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:48:58 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 14:14:15 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_check(const char *haystack, const char *needle)
{
	unsigned long	i;
	int				j;

	i = 0;
	j = 0;
	while (haystack[i] != needle[0] && haystack[i] != '\0')
	{
		j = 0;
		i++;
		while (haystack[i] == needle[j] && haystack[i] != '\0')
		{
			i++;
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)haystack + i - j);
	}
	if (haystack[i] == '\0')
		return (NULL);
	return (0);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	unsigned long	i;

	i = 0;
	if (!haystack || !needle)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			if (ft_check(haystack, needle))
				return (ft_check(haystack, needle));
			else if (ft_strncmp(haystack + i, needle, ft_strlen(needle)) == 0)
				return ((char *)haystack + i);
		}
		i++;
	}
	if (haystack[i] == '\0')
		return (NULL);
	return (0);
}
