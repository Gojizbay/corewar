/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   indcateurs1.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/26 17:23:37 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/03 18:11:25 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		ft_s(t_spec *sp, void *arg)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	if (!arg)
		str = ft_strdup("(null)");
	else
		str = ft_strdup((char*)arg);
	len = pf_strlen(str);
	if (sp->isprec && len > sp->precis)
		len = sp->precis;
	if (sp->largmin && !pf_countchar(sp->attrib, '-'))
		i = i + ft_largminstr(sp, len);
	write(1, str, len);
	if (sp->largmin && pf_countchar(sp->attrib, '-'))
		i = i + ft_largminstr(sp, len);
	ft_strdel(&str);
	return (len + i - sp->len);
}

int		ft_c(t_spec *sp, intmax_t arg)
{
	int		i;
	char	c;

	i = 1;
	if (!arg && sp->isprec && !sp->precis)
		return (write(1, "\0", 1) - sp->len);
	c = arg;
	if (sp->largmin && !pf_countchar(sp->attrib, '-'))
		i = i + ft_largmin(sp, 1, arg);
	if (!arg && sp->isprec && !sp->precis)
		i = i - 1;
	else
		write(1, &c, 1);
	if (sp->largmin && pf_countchar(sp->attrib, '-'))
		i = i + ft_largmin(sp, 1, arg);
	return (i - sp->len);
}

int		ft_uppers(t_spec *sp, void *arg)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_wstrlen((wchar_t*)arg);
	if (!arg)
		arg = ft_strdup("(null)");
	if (sp->isprec && ft_wstrlen((wchar_t *)arg) > sp->precis)
		len = ft_precisionbigs(sp, (wchar_t*)arg);
	if (!checkmcm((wchar_t*)arg, len))
		return (-1 - sp->len);
	if (sp->largmin && !pf_countchar(sp->attrib, '-'))
		i = ft_largminstr(sp, len);
	ft_putstrnw((wchar_t *)arg, len);
	if (sp->largmin && pf_countchar(sp->attrib, '-'))
		i = i + ft_largminstr(sp, len);
	if (!(ft_strcmp(arg, "(null)")))
	{
		free(arg);
		arg = NULL;
	}
	return (len + i - sp->len);
}

int		ft_upperc(t_spec *sp, intmax_t arg)
{
	int		i;
	wchar_t	w;

	if (arg < 0)
		return (-1);
	if (!arg && sp->isprec && !sp->precis)
		return (write(1, "\0", 1) - sp->len);
	w = arg;
	if ((i = sizeofwchar(w)) > MB_CUR_MAX)
		return (-1 - sp->len);
	if (sp->largmin && !pf_countchar(sp->attrib, '-'))
		i = i + ft_largmin(sp, sizeofwchar(w), arg);
	if (!arg && sp->isprec && !sp->precis)
		i = i - 1;
	else
		ft_putwchar(w);
	if (sp->largmin > 0 && pf_countchar(sp->attrib, '-'))
		i = i + ft_largmin(sp, sizeofwchar(w), arg);
	return (i - sp->len);
}

void	ft_n(t_spec *sp, intmax_t *arg, int ret)
{
	if (ft_strcmp(sp->taille, "hh") == 0)
		*arg = (char)ret;
	else if (ft_strcmp(sp->taille, "h") == 0)
		*arg = (short)ret;
	else if (ft_strcmp(sp->taille, "l") == 0)
		*arg = (long)ret;
	else if (ft_strcmp(sp->taille, "ll") == 0)
		*arg = (long long)ret;
	else if (ft_strcmp(sp->taille, "j") == 0)
		*arg = (intmax_t)ret;
	else if (ft_strcmp(sp->taille, "z") == 0)
		*arg = (size_t)ret;
	else
		*arg = (int)ret;
}
