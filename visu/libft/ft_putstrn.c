/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putstrn.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/15 13:43:22 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/19 19:07:34 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstrn(const char *str, int len)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && i < len)
	{
		write(1, str + i, 1);
		i++;
	}
}

void	ft_putstrnw(const wchar_t *str, int len)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0' && j < len)
	{
		ft_putwchar(str[i]);
		j = j + sizeofwchar(str[i]);
		i++;
	}
}
