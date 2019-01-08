/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:48:32 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 17:46:38 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int		wb(char *s, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (j);
}

static int		wd_len(const char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**d;

	i = 0;
	j = 0;
	if (!s || !(d = (char**)malloc(sizeof(char*) * ((wb((char*)s, c) + 1)))))
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		k = 0;
		if (!(d[j] = ((char*)malloc(sizeof(char) * (wd_len(s + i, c) + 1)))))
			return (NULL);
		if (s[i])
		{
			while (s[i] && s[i] != c)
				d[j][k++] = s[i++];
			d[j++][k] = '\0';
		}
	}
	d[j] = NULL;
	return (d);
}
