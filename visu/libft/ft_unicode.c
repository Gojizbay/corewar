/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_unicode.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/23 15:38:57 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/03 17:45:40 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		sizeofwchar(wchar_t w)
{
	int		size;

	size = -1;
	if (w >= 55296 && w <= 57343)
		size = -1;
	else if (w < 128 || (MB_CUR_MAX == 1 && w < 256))
		size = 1;
	else if (w < 2048)
		size = 2;
	else if (w < 65536)
		size = 3;
	else if (w < 1114112)
		size = 4;
	return (size);
}

void	threebytes(wchar_t w)
{
	char	c;

	c = (w >> 12) + 0xE0;
	write(1, &c, 1);
	c = ((w >> 6) & 0x3F) + 0x80;
	write(1, &c, 1);
	c = (w & 0x3F) + 0x80;
	write(1, &c, 1);
}

void	fourbytes(wchar_t w)
{
	char	c;

	c = (w >> 18) + 0xF0;
	write(1, &c, 1);
	c = ((w >> 12) & 0x3F) + 0x80;
	write(1, &c, 1);
	c = ((w >> 6) & 0x3F) + 0x80;
	write(1, &c, 1);
	c = (w & 0x3F) + 0x80;
	write(1, &c, 1);
}

void	ft_putwchar(wchar_t w)
{
	int		size;
	char	c;

	size = sizeofwchar(w);
	if (size == 1)
		write(1, &w, 1);
	if (size == 2)
	{
		c = (w >> 6) + 0xC0;
		write(1, &c, 1);
		c = (w & 0x3F) + 0x80;
		write(1, &c, 1);
	}
	if (size == 3)
		threebytes(w);
	if (size == 4)
		fourbytes(w);
}
