/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:51:00 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 14:59:54 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;

	join = ft_strnew(ft_strlen((char *)s1) + ft_strlen((char *)s2));
	if (join)
	{
		join = ft_strcpy(join, s1);
		join = ft_strcat(join, s2);
	}
	return (join);
}
