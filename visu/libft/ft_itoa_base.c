/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa_base.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/04 14:39:08 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/05 14:12:05 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int			unbrlen(uintmax_t value, int base)
{
	int			len;

	len = 1;
	if (value == 0)
		return (1);
	while (value / base != 0)
	{
		value = value / base;
		len++;
	}
	return (len);
}

uintmax_t	goodcast(intmax_t nbr, char *taille)
{
	if (!ft_strcmp(taille, "hh"))
		return ((unsigned char)nbr);
	else if (!ft_strcmp(taille, "h"))
		return ((unsigned short)nbr);
	else if (!ft_strcmp(taille, "l"))
		return ((unsigned long)nbr);
	else if (!ft_strcmp(taille, "ll"))
		return ((unsigned long long)nbr);
	else if (!ft_strcmp(taille, "j"))
		return ((uintmax_t)nbr);
	else if (!ft_strcmp(taille, "z"))
		return ((size_t)nbr);
	else
		return ((unsigned int)nbr);
}

char		*ft_utoa_base(uintmax_t nbr, int base, char *taille)
{
	int			len;
	char		*s;
	uintmax_t	unbr;

	unbr = goodcast(nbr, taille);
	len = unbrlen(unbr, base);
	if (!(s = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	s[len--] = '\0';
	while (len >= 0)
	{
		s[len--] = (unbr % base <= 9 ?
				unbr % base + 48 : unbr % base + 87);
		unbr = unbr / base;
	}
	return (s);
}
