/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:39:37 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 09:00:50 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void		*ft_memalloc(size_t size)
{
	void	*mem;

	mem = NULL;
	if (size >= 1)
	{
		mem = malloc(size);
		if (mem)
			ft_bzero(mem, size);
	}
	return (mem);
}
