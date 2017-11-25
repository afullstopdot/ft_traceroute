/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:38:28 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 16:42:58 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*next;
	t_list	*tmp;

	tmp = lst;
	next = NULL;
	head = NULL;
	if (tmp)
	{
		head = ft_lstnew(f(tmp)->content, f(tmp)->content_size);
		head->next = next;
		while (tmp->next)
		{
			next = ft_lstnew(f(tmp->next)->content, f(tmp->next)->content_size);
			if (tmp->next)
				next = next->next;
		}
	}
	return (head);
}
