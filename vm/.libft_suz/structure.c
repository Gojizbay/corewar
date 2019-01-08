/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   structure.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/26 13:43:25 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/20 10:51:29 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <ft_printf.h>

void	ft_initialize_struct(t_spec *sp)
{
	sp->attrib = NULL;
	sp->largmin = 0;
	sp->isprec = 0;
	sp->precis = 0;
	sp->taille = NULL;
	sp->indic = '\0';
	sp->len = 0;
	sp->wclarg = 0;
	sp->wcprec = 0;
}

int		size_and_prec(t_spec *sp, char *str, int i)
{
	if (str[i] == '*')
	{
		sp->wclarg = 1;
		i++;
	}
	else if (str[i] && ft_atoi(str + i))
	{
		sp->largmin = ft_atoi(str + i);
		i = i + ft_nblen(ft_atoi(str + i));
	}
	if (str[i] == '.')
	{
		sp->isprec = 1;
		if (str[i + 1] && str[i + 1] != '*')
			sp->precis = ft_atoi(str + ++i);
		else
		{
			sp->wcprec = 1;
			i = i + 2;
		}
		i = ft_isdigit(str[i]) ? i + ft_nblen(ft_atoi(str + i)) : i;
	}
	return (i);
}

void	structdel(t_spec *sp)
{
	ft_strdel(&sp->attrib);
	ft_strdel(&sp->taille);
	free(sp);
}

t_spec	*ft_fill_struct(char *str)
{
	t_spec	*sp;
	int		i;

	i = 0;
	if (!(sp = malloc(sizeof(t_spec))))
		return (0);
	ft_initialize_struct(sp);
	while (pf_countchar(ATTRIB, str[i]))
		i++;
	sp->attrib = i == 0 ? ft_strnew(0) : ft_strsub(str, 0, i);
	i = size_and_prec(sp, str, i);
	if (pf_countchar(TAILLE, str[i]))
	{
		sp->taille = ft_strsub(str, i, pf_countchar(str, str[i]));
		i = i + pf_strlen(sp->taille);
	}
	else
		sp->taille = ft_strnew(0);
	sp->indic = str[i];
	sp->len = i;
	return (sp);
}
