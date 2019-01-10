/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_put_words_table.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:52:09 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/20 16:36:01 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_words_table(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_putstr(tab[i]);
		write(1, "\n", 1);
		i++;
	}
}
