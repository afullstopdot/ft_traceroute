/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:41:27 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 17:37:41 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			count;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	count = 0;
	while (count < n)
	{
		d[count] = s[count];
		count++;
	}
	return (dest);
}
