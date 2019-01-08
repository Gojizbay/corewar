/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   attriblist.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/29 18:28:50 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/03 16:28:17 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_sharp(t_spec *sp, intmax_t arg, int len)
{
	len = len + 0;
	if (sp->indic == 'o' && arg)
	{
		write(1, "0", 1);
		return (1);
	}
	if ((sp->indic == 'x' || sp->indic == 'X') && arg)
	{
		write(1, "0", 1);
		write(1, &(sp->indic), 1);
		return (2);
	}
	return (0);
}

int		display_signs_zero(t_spec *sp, int len, intmax_t arg, int j)
{
	if ((sp->indic == 'd' || sp->indic == 'i') && arg < 0 && len < sp->largmin)
		write(1, "-", 1);
	if ((sp->indic == 'd' || sp->indic == 'i') &&
			pf_countchar(sp->attrib, '+') && arg >= 0 && len < sp->largmin)
	{
		write(1, "+", 1);
		j++;
	}
	return (j);
}

int		ft_zero(t_spec *sp, intmax_t arg, int len)
{
	int j;
	int k;

	j = 0;
	k = 0;
	if (pf_countchar(sp->attrib, ' '))
		k = 1;
	if (!pf_countchar("diouxXb%", sp->indic) ||
			(sp->isprec && sp->indic != '%') || pf_countchar(sp->attrib, '-'))
		return (0);
	if (pf_countchar(sp->attrib, '#') &&
			(sp->indic == 'x' || sp->indic == 'X') && arg)
		j = 2;
	if (pf_countchar(sp->attrib, '#') &&
			(sp->indic == 'o' && arg != 0))
		len++;
	j = display_signs_zero(sp, len, arg, j);
	while (j < sp->largmin - len - k)
	{
		write(1, "0", 1);
		j++;
	}
	return (j);
}

int		ft_space(t_spec *sp, intmax_t arg, int len)
{
	int j;

	j = 0;
	if ((sp->indic != 'd' && sp->indic != 'i') ||
			pf_countchar(sp->attrib, '+') || arg < 0)
		return (0);
	if ((!sp->largmin && arg >= 0) || pf_countchar(sp->attrib, '-'))
	{
		write(1, " ", 1);
		return (1);
	}
	if (j <= sp->largmin - len)
	{
		write(1, " ", 1);
		j++;
	}
	return (j);
}

int		ft_plus(t_spec *sp, intmax_t arg, int len)
{
	if (!pf_countchar("diouxXb", sp->indic))
		return (0);
	if ((sp->indic == 'd' || sp->indic == 'i') &&
		((pf_countchar(sp->attrib, '0') && len < sp->largmin) ||
		sp->precis > len) && arg >= 0)
		return (0);
	if (arg >= 0 && sp->indic != 'u')
	{
		write(1, "+", 1);
		return (1);
	}
	return (0);
}
