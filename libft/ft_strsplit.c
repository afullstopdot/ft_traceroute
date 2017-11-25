/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:55:51 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 18:02:07 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_norme_helper(void)
{
	char	**arr;

	arr = NULL;
	if ((arr = (char **)ft_memalloc(sizeof(char *) * 1)))
		arr[0] = NULL;
	return (arr);
}

static int	ft_arr_size(char const *s, char c)
{
	int		size;
	int		count;

	size = 0;
	count = 0;
	while (s[count] && s[count] == c)
		count++;
	while (s[count])
	{
		while (s[count] && s[count] != c)
			count++;
		size++;
		while (s[count] && s[count] == c)
			count++;
	}
	return (size);
}

static char	*ft_get_next_word(char *s, char c, int *start)
{
	char	*word;
	char	*end;
	int		len;

	word = NULL;
	len = 0;
	if (!(end = ft_strchr(s + *start, c)))
		end = ft_strchr(s, '\0');
	if ((len = end - (s + *start)) > 0)
	{
		word = ft_strsub(s, *start, len);
		*start += len;
	}
	return (word);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		start;
	int		size;
	int		count;

	arr = NULL;
	start = 0;
	count = 0;
	size = ft_arr_size(s, c);
	if (size > 0)
	{
		if ((arr = (char **)ft_memalloc(sizeof(char *) * size + 1)))
		{
			while (count < size)
			{
				while (s[start] == c)
					start++;
				arr[count++] = ft_get_next_word((char *)s, c, &start);
			}
			arr[size] = NULL;
		}
	}
	else
		arr = ft_norme_helper();
	return (arr);
}
