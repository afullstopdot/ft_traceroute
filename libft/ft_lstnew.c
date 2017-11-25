/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:39:00 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 16:14:05 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node)
	{
		if (!content)
		{
			new_node->content = NULL;
			new_node->content_size = 0;
		}
		else
		{
			if ((new_node->content = malloc(content_size)))
			{
				ft_memcpy((new_node->content), content, content_size);
				new_node->content_size = content_size;
			}
		}
		new_node->next = NULL;
	}
	return (new_node);
}
