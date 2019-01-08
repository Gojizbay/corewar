/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:35:52 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/14 17:35:53 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int		nbrlenght(long m)
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

char			*ft_itoa(int n)
{
	long	nb;
	int		i;
	char	*s;
	int		neg;

	neg = 0;
	nb = n;
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
