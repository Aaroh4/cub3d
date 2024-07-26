/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:31:03 by plang             #+#    #+#             */
/*   Updated: 2024/04/17 14:27:57 by plang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* ************************************************************************** */
/*                                 Librarys                                   */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

/* ************************************************************************** */
/*                                BUFFER SIZE                                 */
/* ************************************************************************** */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

/* ************************************************************************** */
/*                                  Structs                                   */
/* ************************************************************************** */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* ************************************************************************** */
/*                              Libft functions                               */
/* ************************************************************************** */

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_atoi(const char *str);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_skip_char(char **str, char c);

/* ************************************************************************** */
/*                              Printf functions                              */
/* ************************************************************************** */

int			ft_putchar(char c, int *ip);
int			ft_puthex_base(unsigned long c, int caps, int *ip);
int			ft_putint_base(int c, int *ip);
int			ft_putpointer(unsigned long adress, int *ip);
int			ft_putstr(char *str, int *ip);
int			ft_putunsig(unsigned int c, int *ip);
int			ft_format_specifier(char specifier, va_list args, int *ip);
int			ft_printf(const char *format, ...);

/* ************************************************************************** */
/*                           Get next line functions                          */
/* ************************************************************************** */

char		*get_next_line(int fd);
char		*ft_get_line(char *read_lines);
char		*ft_get_remainder(char *read_lines);
void		ft_strcpy(char *static_buff, char *temp);
char		*ft_free_gnl(char *read_lines, char *static_buff, int read_bytes);
char		*get_next_line_fd(int fd);
char		*ft_strdup_gnl(const char *s1);
char		*ft_join(char *read_lines, char *static_buff);

#endif
