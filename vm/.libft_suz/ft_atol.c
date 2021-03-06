/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atol.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/02 13:34:21 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/02 13:43:13 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	int		i;
	int		k;
	long	nb;

	i = 0;
	k = 1;
	nb = 0;
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t' ||
				str[i] == '\v' || str[i] == '\n' || str[i] == '\r' ||
				str[i] == '\f'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * k);
}
