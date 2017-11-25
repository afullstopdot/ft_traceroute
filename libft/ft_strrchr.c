/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:55:30 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 13:14:32 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *src, int c)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = NULL;
	while (src[i])
	{
		if (src[i] == (unsigned char)c)
			ptr = ((char *)src) + i;
		i++;
	}
	if (src[i] == (unsigned char)c)
		ptr = ((char *)src) + i;
	return (ptr);
}
