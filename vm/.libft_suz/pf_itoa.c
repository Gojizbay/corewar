/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:35:52 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/20 13:45:31 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdint.h>

static int		nbrlenght(intmax_t m)
{
	long i;

	i = 0;
	if (m == 0)
		return (1);
	if (m < 0)
		i++;
	while (m != 0)
	{
		m = m / 10;
		i++;
	}
	return (i);
}

char			*pf_itoa(intmax_t nb)
{
	int		i;
	char	*s;
	int		neg;

	if (nb == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	neg = 0;
	i = nbrlenght(nb);
	if (!(s = (char *)malloc(sizeof(*s) * (i + 1))))
		return (NULL);
	if (nb < 0)
	{
		neg = 1;
		nb = -nb;
	}
	s[i--] = '\0';
	while (i >= 0)
	{
		s[i--] = nb % 10 + 48;
		nb = nb / 10;
	}
	if (neg)
		s[0] = '-';
	return (s);
}
