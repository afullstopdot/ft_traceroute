/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memccpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:39:55 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 17:36:23 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				count;

	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	count = 0;
	while (count < n)
	{
		d[count] = s[count];
		if (s[count] == (unsigned char)c)
			return (dest + count + 1);
		count++;
	}
	dest = d;
	return (NULL);
}
