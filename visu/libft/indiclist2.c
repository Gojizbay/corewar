/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   indiclist2.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/27 16:14:07 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/28 16:50:54 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_p(t_spec *sp, intmax_t arg)
{
	int			i;

	i = 0;
	if (!arg)
	{
		if (sp->largmin && !pf_countchar(sp->attrib, '-'))
			i = ft_largmin(sp, 3, arg);
		ft_putstr("0x0");
		if (sp->largmin && pf_countchar(sp->attrib, '-'))
			i = i + ft_largmin(sp, 3, arg);
		return (i + 3 - sp->len);
	}
	else
	{
		sp->indic = 'x';
		sp->attrib = pf_strjoin(sp->attrib, "#");
		ft_strdel(&sp->taille);
		sp->taille = ft_strdup("l");
	}
	return (ft_taille(sp, arg));
}

int		ft_d(t_spec *sp, intmax_t arg)
{
	int			tab[2];

	tab[0] = 0;
	tab[1] = ft_nblen(arg);
	if (sp->isprec && sp->precis < sp->largmin)
		tab[0] = tab[0] - 1;
	if (sp->largmin && !pf_countchar(sp->attrib, '-'))
		tab[0] = ft_largmin(sp, tab[1], arg);
	if (isattrib(sp->attrib))
		tab[0] = tab[0] + ft_attributs(sp, arg, tab[1]);
	if (sp->isprec)
		tab[0] = tab[0] + ft_precision(sp, tab[1], arg);
	if (!arg && sp->isprec && !sp->precis)
		tab[0] = tab[0] - 1;
	else if (arg < 0 && (((pf_countchar(sp->attrib, '0') &&
		!pf_countchar(sp->attrib, '-') && tab[1] < sp->largmin)) ||
		(tab[1] <= sp->precis)))
		pf_putnbr(-arg);
	else if (arg == -9223372036854775807 - 1)
		ft_putstr("-9223372036854775808");
	else
		pf_putnbr(arg);
	if (sp->largmin && pf_countchar(sp->attrib, '-'))
		tab[0] = tab[0] + ft_largmin(sp, tab[1], arg);
	return (tab[0] + tab[1] - sp->len);
}

int		ft_i(t_spec *sp, intmax_t arg)
{
	int			tab[2];

	tab[0] = 0;
	tab[1] = ft_nblen(arg);
	if (sp->isprec && sp->precis < sp->largmin)
		tab[0] = tab[0] - 1;
	if (sp->largmin && !pf_countchar(sp->attrib, '-'))
		tab[0] = ft_largmin(sp, tab[1], arg);
	if (isattrib(sp->attrib))
		tab[0] = tab[0] + ft_attributs(sp, arg, tab[1]);
	if (sp->isprec)
		tab[0] = tab[0] + ft_precision(sp, tab[1], arg);
	if (!arg && sp->isprec && !sp->precis)
		tab[0] = tab[0] - 1;
	else if (arg < 0 && (((pf_countchar(sp->attrib, '0') &&
		!pf_countchar(sp->attrib, '-') && tab[1] < sp->largmin)) ||
		(tab[1] <= sp->precis)))
		pf_putnbr(-arg);
	else if (arg == -9223372036854775807 - 1)
		ft_putstr("-9223372036854775808");
	else
		pf_putnbr(arg);
	if (sp->largmin && pf_countchar(sp->attrib, '-'))
		tab[0] = tab[0] + ft_largmin(sp, tab[1], arg);
	return (tab[0] + tab[1] - sp->len);
}

int		ft_o(t_spec *sp, intmax_t arg)
{
	int			i;
	char		*s;
	int			len;

	if (!(s = ft_utoa_base(arg, 8, sp->taille)))
		return (-1);
	len = pf_strlen(s);
	i = 0;
	if (sp->largmin && !pf_countchar(sp->attrib, '-'))
		i = ft_largmin(sp, len, arg);
	if (isattrib(sp->attrib))
		i = i + ft_attributs(sp, arg, len);
	if (sp->isprec)
		i = i + ft_precision(sp, len, arg);
	if (!arg && sp->isprec && !sp->precis && !pf_countchar(sp->attrib, '#'))
		i = (sp->largmin && pf_countchar(sp->attrib, '-') ? i - 2 : i - 1);
	else
		write(1, s, len);
	if (sp->largmin && pf_countchar(sp->attrib, '-'))
		i = i + ft_largmin(sp, len, arg);
	ft_strdel(&s);
	return (i + len - sp->len);
}

int		ft_u(t_spec *sp, intmax_t arg)
{
	int			i;
	int			len;
	uintmax_t	ar;

	i = 0;
	if (sp->isprec && sp->precis < sp->largmin)
		i = i - 1;
	if (arg < 0)
		ar = goodcast(arg, sp->taille);
	else
		ar = arg;
	len = ft_unblen(ar);
	if (sp->largmin && !pf_countchar(sp->attrib, '-'))
		i = ft_largmin(sp, len, ar);
	if (isattrib(sp->attrib))
		i = i + ft_attributs(sp, ar, len);
	if (sp->isprec)
		i = i + ft_precision(sp, len, ar);
	if (!arg && sp->isprec && !sp->precis)
		i = i - 1;
	else
		ft_putunbr(ar);
	if (sp->largmin && pf_countchar(sp->attrib, '-'))
		i = i + ft_largmin(sp, len, ar);
	return (i + len - sp->len);
}
