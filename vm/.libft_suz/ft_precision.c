/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_precision.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 18:16:55 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/23 18:09:55 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_precisionbigs(t_spec *sp, wchar_t *arg)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (arg[i] && j <= sp->precis)
	{
		k = j;
		j = k + sizeofwchar(arg[i]);
		i++;
	}
	return (k);
}

int		ft_precision(t_spec *sp, int len, intmax_t arg)
{
	int		i;
	int		j;

	i = 0;
	j = len;
	if (sp->indic == 'o' && pf_countchar(sp->attrib, '#') && arg)
		len++;
	if ((sp->indic == 'd' || sp->indic == 'i') && arg < 0 &&
		len <= sp->precis)
	{
		write(1, "-", 1);
		len--;
	}
	if ((sp->indic == 'd' || sp->indic == 'i') &&
		len < sp->precis && pf_countchar(sp->attrib, '+') && arg >= 0)
	{
		write(1, "+", 1);
		i++;
	}
	while (sp->precis && sp->precis > len++)
	{
		write(1, "0", 1);
		i++;
	}
	return (i);
}
