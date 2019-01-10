/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_putnbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:41:03 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/13 13:23:13 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putnbr(intmax_t nb)
{
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		pf_putnbr(nb / 10);
		ft_putwchar(nb % 10 + '0');
	}
	else
		ft_putwchar(nb + '0');
}

void	ft_putunbr(unsigned long long nb)
{
	if (nb >= 10)
	{
		pf_putnbr(nb / 10);
		ft_putwchar(nb % 10 + '0');
	}
	else
		ft_putwchar(nb + '0');
}
