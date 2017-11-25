/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:52:37 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 08:52:44 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*new;
	size_t	count;

	count = 0;
	new = ft_strnew(ft_strlen((char *)s));
	if (new)
	{
		while (s[count])
		{
			new[count] = f(s[count]);
			count++;
		}
	}
	return (new);
}
