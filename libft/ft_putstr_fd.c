/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:46:43 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 08:46:51 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putstr_fd(char const *s, int fd)
{
	size_t	count;

	count = 0;
	while (s[count])
		ft_putchar_fd(s[count++], fd);
}
