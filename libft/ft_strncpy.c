/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:53:58 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 08:54:04 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	k;

	k = 0;
	while (src[k] && k < n)
	{
		dest[k] = src[k];
		k++;
	}
	while (k < n)
		dest[k++] = '\0';
	return (dest);
}
