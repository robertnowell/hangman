/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnowell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 11:29:21 by rnowell           #+#    #+#             */
/*   Updated: 2016/11/13 11:29:23 by rnowell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>

# define BUFF_SIZE 200

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_struct
{
	char			*s;
	int				fdesc;
	char			*index;
	struct s_struct *next;
}					t_struct;

/*
** get next line
*/

int get_next_line(const int fd, char **line);

/*
** print to file
*/
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnbr_base_fd(long n, int base, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_set_print_color_to(int color);

/*
** print to standard output/error
*/
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putstr_digits(char *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_set_print_color_to(int color);
void				ft_puterr(char const *msg);

/*
** analyze char
*/
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isspace(int c);
int					ft_isspacelinetab(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				ft_trans_toupper(char *c);
void				ft_trans_tolower(char *c);

/*
** analyze string
*/
size_t				ft_strlen(char const *s);
int					ft_strlen_until(char *s, char c);
char				*ft_strcpy(char *dst, char const *src);
char				*ft_strncpy(char *dst, char const *src, size_t len);
char				*ft_strdup(char const *s1);
char				*ft_strdup_until(char *s, char c);
char				*ft_strcat(char *s1, char const *s2);
char				*ft_strncat(char *s1, char const *s2, size_t n);
size_t				ft_strlcat(char *dst, char const *src, size_t size);
int					ft_strcmp(char const *s1, char const *s2);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
char				*ft_strchr(char const *s, int c);
char				*ft_strrchr(char const *s, int c);
char				*ft_strstr(char const *big, char const *small);
char				*ft_strnstr(char const *big, char const *small, size_t len);
char				*ft_skip_spaces(char const *s);
char				*ft_skip_delim(char const *s, char c);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strltrim(char const *s);
char				*ft_strrtrim(char const *s);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
int					ft_wordcount(char const *str, char c);
char				*ft_strrev(char *s);

/*
** int
*/
int					ft_atoi(char const *str);
int					ft_atoi_base(char const *str, int base);
char				*ft_itoa(int n);
char				*ft_itoa_base(int n, int base);
int					ft_count_digits(int n, int base);

/*
** memory
*/

void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, void const *src, size_t n);
void				*ft_memccpy(void *dst, void const *src, int c, size_t n);
void				*ft_memmove(void *dst, void const *src, size_t len);
void				*ft_memchr(void const *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
int					ft_memcmp(void const *s1, const void *s2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);

/*
** list
*/

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** lists for t_struct
*/
t_struct			*ft_lst_clone(t_struct *node);
void				ft_lst_push_back(t_struct **l, char *s, int fd, char *s2);
t_struct			*ft_create_elem(char *content, int fd, char *endl_index);
void				ft_lstdel_if(t_struct **begin_list, int fd);
void				ft_lstdel_tstruct(t_struct **alst);
void				ft_lstdelone_tstruct(t_struct **alst);

#endif
