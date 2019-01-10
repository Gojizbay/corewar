/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:47:59 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/14 17:48:00 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	if (ft_strcmp(haystack, needle) == 0)
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		while (haystack[i] != needle[0] && haystack[i] != '\0')
			i++;
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j] != '\0' &&
				(i + j) < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		if (haystack[i] != '\0')
			i++;
	}
	if (haystack[i] == '\0' || (i = len && needle[j] != '\0'))
		return (NULL);
	return (0);
}
