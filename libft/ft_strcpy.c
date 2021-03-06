/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:48:21 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 08:48:27 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcpy(char *dest, const char *src)
{
	int		k;

	k = 0;
	while (src[k])
	{
		dest[k] = ((char *)src)[k];
		k++;
	}
	dest[k] = '\0';
	return (dest);
}
