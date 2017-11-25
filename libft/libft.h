/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:53:02 by amarquez          #+#    #+#             */
/*   Updated: 2017/06/20 13:19:14 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** Re-coding basic C functions.
**
** Define Headers, only allowed to use malloc, free and write
*/

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

/*
** defines and structs
*/

# define TRUE 1
# define FALSE 0
# define FT_ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

/*
** --- Mandatory Part ---
** generic functions
*/

void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memset(void *src, int c, size_t n);
void				*ft_memalloc(size_t size);
void				ft_bzero(void *src, size_t n);
void				ft_memdel(void **ap);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/*
** character functions, checking if they fall under certain rules.
*/

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);

/*
** string functions.
*/

void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *str);
void				ft_putstr_fd(char const *str, int fd);
void				ft_putendl(char const *str);
void				ft_putendl_fd(char const *str, int fd);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t				ft_strlen(char *src);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_atoi(char const *nptr);
char				*ft_itoa(int n);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strdup(const char *src);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
char				*ft_strchr(const char *src, int c);
char				*ft_strrchr(const char *src, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *big, const char *needle, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strmap(char const *string, char (*func)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);

/*
** Bonus Part
*/

void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstcontentdel(void *content, size_t content_size);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);

#endif
