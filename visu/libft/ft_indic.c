/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_indic.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/26 15:44:15 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/02 16:14:41 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_indicchar(t_spec *sp, void *arg)
{
	int		i;

	i = 0;
	if (sp->indic == 's')
		i = ft_s(sp, arg);
	if (sp->indic == 'S')
		i = ft_uppers(sp, arg);
	return (i);
}

int		ft_indiclong(t_spec *sp, intmax_t arg)
{
	int		(*f[12])(t_spec *, intmax_t);
	int		i;

	i = 0;
	f[1] = ft_p;
	f[2] = ft_d;
	f[3] = ft_i;
	f[4] = ft_o;
	f[5] = ft_u;
	f[6] = ft_x;
	f[7] = ft_upperx;
	f[8] = ft_b;
	f[9] = ft_c;
	f[10] = ft_upperc;
	f[11] = ft_mod;
	i = f[isindicint(sp->indic)](sp, arg);
	return (i);
}
