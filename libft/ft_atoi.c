/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:34:00 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 14:51:57 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	char	*ascii;
	int		index;
	int		n;
	int		negative;

	index = 0;
	n = 0;
	negative = FALSE;
	ascii = ft_strtrim(str);
	if (ascii)
	{
		if (ascii[index] == '-' || ascii[index] == '+')
			if (ascii[index++] == '-')
				negative = TRUE;
		while (ft_isdigit(ascii[index]))
			n = (n * 10) + (ascii[index++] - '0');
		ft_strdel(&ascii);
		if (negative == TRUE)
			return (-(n));
	}
	return (n);
}
