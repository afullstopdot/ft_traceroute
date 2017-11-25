/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmapi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:53:01 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 08:53:06 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	size_t	count;

	count = 0;
	new = ft_strnew(ft_strlen((char *)s));
	if (new)
	{
		while (s[count])
		{
			new[count] = f(count, s[count]);
			count++;
		}
	}
	return (new);
}
