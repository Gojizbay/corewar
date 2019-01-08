/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   isattrib.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/09 13:21:56 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/02 16:44:34 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		isattrib(char *s)
{
	if (!s)
		return (0);
	if (ft_charstrstr(ATTRIB, s) || pf_countchar(ATTRIB, s[0]))
		return (1);
	return (0);
}

int		isindic(char c)
{
	if (pf_countchar(INDIC, c))
		return (1);
	return (0);
}

int		isindicint(char c)
{
	int		i;

	i = 0;
	if (pf_countchar("pdiouxXbcC%", c))
		return (ft_charpos("pdiouxXbcC%", c) + 1);
	return (0);
}
