/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:36:15 by mraspors          #+#    #+#             */
/*   Updated: 2022/01/27 05:38:43 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_list;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (new_list == NULL)
			new_list = new_node;
		else
			ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	ft_lstclear(&lst, del);
	return (new_list);
}
