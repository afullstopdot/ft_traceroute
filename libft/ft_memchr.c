/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:40:31 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 11:55:30 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*mem;
	unsigned char	instance;
	size_t			count;

	mem = (unsigned char *)s;
	instance = (unsigned char)c;
	count = 0;
	while (count < n)
	{
		if (mem[count] == instance)
			return ((void *)s + count);
		count++;
	}
	return (NULL);
}
