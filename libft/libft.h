/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:08:20 by fherbine          #+#    #+#             */
/*   Updated: 2018/09/08 04:12:38 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <inttypes.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <stdarg.h>
# include <dirent.h>
# include "libsh/libsh.h"
# include "defines/ansi.h"
# include "defines/references.h"

# define BUFF_SIZE 32

typedef	struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

typedef struct			s_gnl
{
	char				buf[BUFF_SIZE + 1];
	int					j;
	int					fd;
	struct s_gnl		*next;
}						t_gnl;

size_t					ft_strlen(const char *s);

char					*ft_strdup(const char *s1);

char					*ft_strcpy(char *dst, const char *src);

char					*ft_strncpy(char *dst, const char *src, size_t len);

char					*ft_strcat(char *s1, const char *s2);

char					*ft_strncat(char *s1, const char *s2, size_t n);

size_t					ft_strlcat(char *dst, const char *src, size_t size);

char					*ft_strchr(const char *s, int c);

char					*ft_strrchr(const char *s, int c);

char					*ft_strstr(const char *haystack, const char *needle);

char					*ft_strnstr(const char *haystack, const char *needle, \
		size_t len);

int						ft_strcmp(const char *s1, const char *s2);

int						ft_strncmp(const char *s1, const char *s2, size_t n);

int						ft_atoi(const char *str);

int						ft_isalnum(int c);

int						ft_isalpha(int c);

int						ft_isascii(int c);

int						ft_isdigit(int c);

int						ft_isprint(int c);

int						ft_tolower(int c);

int						ft_toupper(int c);

void					ft_bzero(void *s, size_t n);

void					*ft_memchr(const void *s, int c, size_t n);

int						ft_memcmp(const void *s1, const void *s2, size_t n);

void					*ft_memcpy(void *dst, const void *src, size_t n);

void					*ft_memccpy(void *dst, const void *src, int c, size_t \
		n);

void					*ft_memmove(void *dst, const void *src, size_t len);

void					*ft_memset(void *b, int c, size_t len);

void					*ft_memalloc(size_t size);

void					ft_memdel(void **ap);

void					ft_strclr(char *s);

void					ft_strdel(char **as);

void					ft_striter(char *s, void (*f)(char *));

void					ft_striteri(char *s, void (*f)(unsigned int, char *));

char					*ft_strnew(size_t size);

char					*ft_strmap(const char *s, char (*f)(char));

char					*ft_strmapi(const char *s, char \
		(*f)(unsigned int, char));

int						ft_strequ(char const *s1, char const *s2);

int						ft_strnequ(char const *s1, char const *s2, size_t n);

char					*ft_strsub(const char *s, unsigned int start, size_t \
		len);

char					*ft_strjoin(char *s1, const char *s2);

char					*ft_strtrim(const char *s);

char					*ft_itoa(intmax_t n);

char					**ft_strsplit(char const *s, char c);

void					ft_putchar(char c);

void					ft_putchar_fd(char c, int fd);

void					ft_putstr(char const *s);

void					ft_putstr_fd(char const *s, int fd);

void					ft_putendl(char const *s);

void					ft_putendl_fd(char const *s, int fd);

void					ft_putnbr(intmax_t n);

void					ft_putnbr_fd(int n, int fd);

t_list					*ft_lstnew(void const *content, size_t content_size);

void					ft_lstdelone(t_list **alst, void \
		(*del)(void *, size_t));

void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));

void					ft_lstadd(t_list **alst, t_list *new);

void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));

t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

void					ft_swap(int *a, int *b);

int						ft_str_is_printable(char *str);

void					ft_putnbr_base(uintmax_t n, char *base);

int						get_next_line(const int fd, char **line);

int						ft_gnl(char **line, t_gnl *gnl);

int						ft_read(char **line, char *str, t_gnl *gnl);

int						ft_absol(int n);

int						ft_nlen_base(uintmax_t n, int base);

int						ft_nlen_10(intmax_t n);

char					*ft_itoa_base(uintmax_t n, uintmax_t base);

int						ft_prints_fd(int fd, char *format, ...);

int						ft_prints(char *format, ...);

char					*ft_di(intmax_t n, char *str);

char					*ft_xo(uintmax_t n, char *str, char param);

char					*ft_s(char *str2, char *str);

char					*ft_c(int c, char *str);

void					ft_put_n_char(int n, int c);

char					*ft_append_slash(char *path);

int						ftsh_cwdgit(char *p_cwd);

char					*ftsh_get_np(char *path);

int						ft_is_in_dir(char *name, char *path);

int						ftsh_ispath(char *path);

int						ft_tab_len(char **tab);

void					ft_free_tab(char **tab);

char					**ft_tab_del_elem(char **tab, char *name);

char					**ft_copy_tab(char **tab);

char					**ft_add_tab_elem(char **tab, char *elem);

char					*ft_getenv(char **envp, char *search);

void					ft_capitalize(char **p_str);

uint8_t					ft_strinarray(char **haystack, char *needle);

double					ft_sqrt(double nb);

#endif
