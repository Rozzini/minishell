/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:16:10 by mraspors          #+#    #+#             */
/*   Updated: 2022/08/14 13:15:17 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_calloc(size_t nitems, size_t size);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));

int			ft_memcmp(const void *str1, const void *str2, size_t n);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);
int			ft_lstsize(t_list *lst);
int			ft_strcmp(char *s1, char *s2);

size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);

char		*ft_strstr(char *str, char *to_find);
char		*ft_strcat(char *dest, char *src);
char		*ft_strdup(const char *string);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		**ft_split(char const *s, char c);

int			ft_printf(const char *str, ...);
int			ft_print_uint(unsigned int nbr);
int			ft_print_string(char *str);
int			ft_print_pointer(unsigned long ptr);
int			ft_print_number(int nbr);
int			ft_print_hex(unsigned int num, char c);
int			ft_print_char(char c);

t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

char		*get_next_line(int fd);
char		*ft_read(int fd, char *buf, int *loc);
char		*create_result(char *buf, int loc);
char		*fill_buf(char *buf, int loc);
int			ft_strlen_gnl(char *s);
int			ft_strchr_gnl(char *str, int *i, int *give_loc);
char		*ft_strjoin_gnl(char *s1, char *s2);

#endif