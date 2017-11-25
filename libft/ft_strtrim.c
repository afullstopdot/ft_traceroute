/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:56:52 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 18:03:12 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\r'
			|| c == '\f');
}

static int			ft_empty(char const *s)
{
	int				size;
	int				count;

	size = 0;
	count = 0;
	while (s[count])
	{
		if (ft_isspace(s[count]))
			size++;
		count++;
	}
	return (size == count);
}

static unsigned	int	*ft_start_end(char const *s)
{
	unsigned int	*start_end;

	if ((start_end = (unsigned int *)malloc(sizeof(unsigned int) * 2)))
	{
		start_end[0] = 0;
		start_end[1] = ft_strlen((char *)s) - 1;
		while (s[start_end[0]])
		{
			if (!ft_isspace(s[start_end[0]]))
				break ;
			start_end[0]++;
		}
		while (start_end[1] > 0)
		{
			if (!ft_isspace(s[start_end[1]]))
				break ;
			start_end[1]--;
		}
	}
	return (start_end);
}

char				*ft_strtrim(char const *s)
{
	char			*copy;
	unsigned int	*start_end;
	int				len;

	copy = NULL;
	start_end = NULL;
	len = 0;
	if (ft_empty(s) == 1)
		return (ft_strdup(""));
	if (s)
	{
		if ((start_end = ft_start_end(s)))
		{
			len = start_end[1] - start_end[0] + 1;
			copy = ft_strsub(s, start_end[0], len);
			free(start_end);
		}
	}
	return (copy);
}
