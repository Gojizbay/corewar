/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 09:45:07 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 14:12:23 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_tmp(char **str, char *buf)
{
	char	*tmp;

	if (!*str)
	{
		if (!(*str = ft_strdup(buf)))
			return (-1);
	}
	else
	{
		if (!(tmp = ft_strdup(*str)))
			return (-1);
		ft_strdel(str);
		if (!(*str = ft_strjoin(tmp, buf)))
			return (-1);
		ft_strdel(&tmp);
	}
	return (0);
}

int		nl_in_str(char **str, char **line)
{
	char *tmp;

	if (ft_strcmp(*str, "\n") == 0)
	{
		if (!(*line = ft_strnew(0)))
			return (-1);
		ft_strdel(str);
		return (0);
	}
	if (*str[0] == '\n')
	{
		if (!(*line = ft_strnew(0)) ||
				!(*str = ft_strsub(*str, 1, ft_strlen(*str) - 1)))
			return (-1);
		return (0);
	}
	if (!(*line = ft_strsub(*str, 0, ft_charpos(*str, '\n'))) ||
			!(tmp = ft_strdup(*str)))
		return (-1);
	ft_strdel(str);
	if (!(*str = ft_strsub(tmp, ft_charpos(tmp, '\n') + 1,
					ft_strlen(tmp) - ft_charpos(tmp, '\n'))))
		return (-1);
	ft_strdel(&tmp);
	return (0);
}

int		if_str(char **str, char **line, int ret)
{
	if (ft_countchar(*str, '\n') > 0)
	{
		return (nl_in_str(str, line));
	}
	else if (ret < BUFF_SIZE)
	{
		if (!(*line = ft_strdup(*str)))
			return (-1);
		ft_strdel(str);
	}
	return (0);
}

int		ft_concat(char **str, char **line, int ret)
{
	if (ret == 0 && *str && !(ft_countchar(*str, '\n')))
	{
		if (!(ft_strcmp(*str, "\0")))
		{
			ft_strdel(str);
			return (0);
		}
		if (!(*line = ft_strdup(*str)))
			return (-1);
		ft_strdel(str);
		return (1);
	}
	if (*str)
	{
		if (if_str(str, line, ret) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char	*str;
	int			ret;
	char		buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || read(fd, buf, 0) < 0)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (ft_countchar(buf, '\n'))
		{
			if (ft_tmp(&str, buf) == -1)
				return (-1);
			break ;
		}
		if (ft_tmp(&str, buf) == -1)
			return (-1);
	}
	if (ft_concat(&str, line, ret) == 1)
		return (1);
	*line = NULL;
	ft_strdel(line);
	return (ret < 0 ? -1 : 0);
}
