/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:41:12 by aduchemi          #+#    #+#             */
/*   Updated: 2019/10/22 14:56:30 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_fail_new(t_list **begin, void (*del)(void *))
{
	if (del && begin)
	{
		while (*begin)
		{
			del((*begin)->content);
			free(*begin);
			(*begin) = (*begin)->next;
		}
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*elem;
	t_list	*begin;

	if (!f)
		return (0);
	elem = NULL;
	begin = elem;
	while (lst)
	{
		if (!(elem = ft_lstnew(f(lst->content))))
		{
			elem = begin;
			ft_lst_fail_new(&begin, (*del));
			begin = elem;
			begin->next = NULL;
		}
		else
		{
			ft_lstadd_back(&begin, elem);
			elem = elem->next;
			lst = lst->next;
		}
	}
	return (begin);
}
