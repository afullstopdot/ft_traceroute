/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:49:07 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 14:18:33 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *src)
{
	char	*str;
	int		len;

	len = ft_strlen((char *)src);
	str = ft_strnew(len);
	if (str)
	{
		str = ft_strcpy(str, src);
		return (str);
	}
	return (NULL);
}
