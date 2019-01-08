/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:37:00 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/14 17:37:02 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int		count(t_list *lst, int i)
{
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f) (t_list *elem))
{
	t_list **d;

	if (lst && f)
	{
		if (!(d = malloc(sizeof(d) * count(lst, 1))))
			return (NULL);
		if (!(*d = ft_lstnew((f(lst))->content, f((lst))->content_size)))
			return (NULL);
		if (lst->next != NULL)
			(*d)->next = ft_lstmap(lst->next, f);
		else
			(*d)->next = NULL;
		return (*d);
	}
	return (NULL);
}
