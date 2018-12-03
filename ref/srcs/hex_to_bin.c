/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hex_to_bin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bodibon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/28 14:34:01 by bodibon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/28 14:34:03 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

unsigned char		*hex_to_bin(char *str)
{
	unsigned int	i;
	unsigned int	j;
	unsigned char	c;
	unsigned char	*bin;

	i = 0;
	j = 0;
	if (!(bin = (unsigned char*)malloc(sizeof(unsigned char)
					* (strlen(str) / 2 + 1))))
		return (NULL);
	while (str[i])
	{
		if (str[i + 1] == '\0')
			exit(EXIT_FAILURE);
		if (str[i] >= '0' && str[i] <= '9')
			c = (str[i] - '0') << 4;
		else if (str[i] >= 'a' && str[i] <= 'f')
			c = (str[i] - 'a' + 10) << 4;
		if (str[i + 1] >= '0' && str[i + 1] <= '9')
			c |= (str[i + 1] - '0');
		else if (str[i + 1] >= 'a' && str[i + 1] <= 'f')
			c |= (str[i + 1] - 'a' + 10);
		bin[j] = c;
		j++;
		i += 2;
	}
	bin[j] = '\0';
	return (bin);
}
