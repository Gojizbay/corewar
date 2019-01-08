/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   manage_nega.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/25 21:31:52 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/18 20:34:16 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		manage_nega(t_arg_type type, int dirsize, int val)
{
	int		ret;

	ret = val;
	if (val & 0x8000)
	{
		if (type == T_IND || (type == T_DIR && dirsize == 2))
			ret = -((val ^ 0xFFFF) + 1);
		else if (type == T_DIR && dirsize == 4)
			ret = -((val ^ 0xFFFFFFFF) + 1);
	}
	return (ret);
}
