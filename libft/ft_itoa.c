/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:35:42 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 18:05:30 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_convert(int n, int b, char *ascii, int *index)
{
	char	base[17];

	ft_strcpy(base, "0123456789ABCDEF");
	if (n <= -b || b <= n)
		ft_convert(n / b, b, ascii, index);
	ascii[(*index)++] = base[FT_ABS(n % b)];
}

char		*ft_itoa(int n)
{
	char	*ascii;
	int		index;

	index = 0;
	ascii = ft_strnew(35);
	if (ascii)
	{
		if (n < 0)
			ascii[index++] = '-';
		ft_convert(n, 10, ascii, &index);
	}
	return (ascii);
}
