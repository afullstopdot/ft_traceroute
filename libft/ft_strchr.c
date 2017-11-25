/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:47:33 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 13:12:56 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *src, int c)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (src[i] == (unsigned char)c)
			return ((char *)(src + i));
		i++;
	}
	if (src[i] == (unsigned char)c)
		return ((char *)(src + i));
	return (NULL);
}
