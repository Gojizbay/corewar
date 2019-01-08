/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/21 16:57:06 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/05 13:54:18 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	bigindic(t_spec *sp)
{
	if (pf_countchar("DOU", sp->indic) == 1)
	{
		ft_strdel(&sp->taille);
		sp->taille = ft_strdup("l");
		sp->indic = ft_tolower(sp->indic);
	}
	if ((sp->indic == 'c' || sp->indic == 's') && !ft_strcmp(sp->taille, "l"))
	{
		sp->indic = sp->indic - 32;
		ft_strdel(&sp->taille);
		sp->taille = ft_strnew(0);
	}
	if (sp->indic == 'p')
	{
		ft_strdel(&sp->taille);
		sp->taille = ft_strdup("l");
	}
}

int		treat_struct(va_list va, t_spec *sp)
{
	int		ret;

	ret = 0;
	if (sp->wclarg)
		sp->largmin = va_arg(va, int);
	if (sp->wcprec)
		sp->precis = va_arg(va, int);
	if (sp->indic == 's' || sp->indic == 'S')
	{
		if ((ret = ft_indicchar(sp, va_arg(va, void *))) == -1 - sp->len)
			return (-1 - sp->len);
	}
	else if (pf_countchar("pdiouxXbcC%", sp->indic) == 1)
	{
		if (sp->indic == '%')
			ret = ft_taille(sp, '%');
		else if ((ret = ft_taille(sp, va_arg(va, intmax_t))) == -1 - sp->len)
			return (-1 - sp->len);
	}
	return (ret);
}

int		fucknorm(int *tab, char *str, va_list va, t_spec *sp)
{
	if ((tab[4] = treat_struct(va, sp)) == -1 - sp->len)
	{
		structdel(sp);
		ft_strdel(&str);
		va_end(va);
		return (-1 - sp->len);
	}
	tab[3] = tab[3] + tab[4];
	tab[0] = tab[0] + pf_strlen(str);
	ft_strdel(&str);
	tab[1] = tab[0];
	tab[2] = tab[2] + 2;
	if (sp->indic == 'n')
		ft_n(sp, va_arg(va, intmax_t*), tab[3] + tab[0] - tab[2]);
	structdel(sp);
	return (0);
}

int		fucknorm2(int *tab, va_list va, char *format)
{
	if (format[tab[0]] == '\0')
	{
		ft_putstr(format + tab[1]);
		va_end(va);
		return (tab[3] + tab[0] - tab[2]);
	}
	else
		tab[0]++;
	write(1, format + tab[1], tab[0] - tab[1] - 1);
	return (-2);
}

int		ft_printf(const char *format, ...)
{
	int		tab[6];
	va_list	va;
	char	*str;
	t_spec	*sp;

	va_start(va, format);
	init_tab(tab);
	while (format[tab[0]] != '\0')
	{
		while (format[tab[0]] != '%' && format[tab[0]] != '\0')
			tab[0]++;
		if ((tab[5] = fucknorm2(tab, va, (char*)format)) != -2)
			return (tab[5]);
		if (!(str = ft_strsub(format, tab[0],
						ft_charstrstr(format + tab[0], INDIC) + 1)))
			return (0);
		sp = ft_fill_struct(str);
		bigindic(sp);
		if (fucknorm(tab, str, va, sp) == -1 - sp->len)
			return (-1);
	}
	ft_putstr(format + tab[1]);
	tab[3] = tab[3] + tab[0] - tab[2];
	va_end(va);
	return (tab[3]);
}
