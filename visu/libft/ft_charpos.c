/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_charpos.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/22 17:56:23 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/22 18:00:51 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_charpos(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (0);
}
