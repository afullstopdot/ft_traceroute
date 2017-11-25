/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 09:11:36 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 17:38:03 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	const char		*s;
	size_t			count;

	s = (const char *)src;
	d = (unsigned char *)dest;
	count = 0;
	if (dest == src)
		return (dest);
	if (src > dest)
		ft_memcpy(dest, src, n);
	else
	{
		while (count < n--)
			d[count + n] = s[count + n];
	}
	return (dest);
}
