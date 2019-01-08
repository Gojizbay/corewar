/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mem_tools.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/30 16:47:30 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/08 16:14:58 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		read_mem(unsigned char *mem, int start, size_t bytes)
{
	int		i;
	int		ret;
	int		pos;

	i = 0;
	ret = 0;
	while (i < bytes)
	{
		pos = (MEM_SIZE + start - i) % MEM_SIZE;
		ret += mem[pos] << (i * 8);
		i++;
	}
	return (ret);
}

void	write_mem(unsigned char *mem, int start, size_t bytes, int val)
{
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	while (i < bytes)
	{
		pos = (MEM_SIZE + start - i) % MEM_SIZE;
		mem[pos] = (val >> (i * 8)) & 0xFF;
		i++;
	}
}
