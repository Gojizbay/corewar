/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_taille.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/20 15:17:49 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/23 17:27:47 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_taille(t_spec *sp, intmax_t arg)
{
	int		ret;

	if (ft_strcmp(sp->taille, "hh") == 0)
		ret = sp->indic == 'u' ? ft_indiclong(sp, (unsigned char)arg) :
			ft_indiclong(sp, (char)arg);
	else if (ft_strcmp(sp->taille, "h") == 0)
		ret = ft_indiclong(sp, (short)arg);
	else if (ft_strcmp(sp->taille, "l") == 0)
		ret = ft_indiclong(sp, (long int)arg);
	else if (ft_strcmp(sp->taille, "ll") == 0)
		ret = ft_indiclong(sp, (long long int)arg);
	else if (ft_strcmp(sp->taille, "j") == 0)
		ret = ft_indiclong(sp, arg);
	else if (ft_strcmp(sp->taille, "z") == 0)
		ret = ft_indiclong(sp, (size_t)arg);
	else
		ret = ft_indiclong(sp, (int)arg);
	return (ret);
}
