/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_largmin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/07 13:54:30 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/03 15:04:43 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		nolargmin(t_spec *sp)
{
	if ((sp->isprec && sp->precis >= sp->largmin) ||
			(!pf_countchar(sp->attrib, '-') && pf_countchar(sp->attrib, '0') &&
			sp->precis >= sp->largmin) || (!pf_countchar(sp->attrib, '-') &&
		pf_countchar(sp->attrib, '0') && !sp->isprec) ||
			(sp->isprec && sp->precis > sp->largmin))
		return (0);
	return (1);
}

int		calck(t_spec *sp, int len, intmax_t arg)
{
	int		k;

	k = 0;
	if (arg && pf_countchar(sp->attrib, '#') && (sp->indic == 'x' ||
				sp->indic == 'X'))
		k = 2;
	if ((arg && pf_countchar(sp->attrib, '#') && sp->indic == 'o' &&
			(!sp->isprec || sp->precis <= len)) ||
			((pf_countchar(sp->attrib, ' ') ||
			pf_countchar(sp->attrib, '+')) && sp->indic != '%'))
		k = 1;
	return (k);
}

int		ft_largmin(t_spec *sp, int len, intmax_t arg)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!nolargmin(sp))
		return (0);
	if (!arg && sp->isprec && !sp->precis)
		len = 0;
	k = calck(sp, len, arg);
	if (sp->isprec && sp->precis < sp->largmin && sp->precis >= len &&
			sp->indic != '%')
		k = k + sp->precis - len;
	if (sp->isprec && sp->largmin > len && arg < 0 && sp->precis >= len)
		k++;
	while (i < sp->largmin - len - k)
	{
		write(1, " ", 1);
		i++;
	}
	if (pf_countchar("diu", sp->indic) && sp->isprec &&
			pf_countchar(sp->attrib, '-'))
		i++;
	return (i);
}

int		ft_largminstr(t_spec *sp, int len)
{
	int		i;

	i = 0;
	while (i < sp->largmin - len)
	{
		write(1, " ", 1);
		i++;
	}
	return (i);
}
