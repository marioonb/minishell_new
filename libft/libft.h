/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:53:29 by mbelorge          #+#    #+#             */
/*   Updated: 2020/01/03 17:17:24 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

# define BUFFER_SIZE 100

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*
** LIBFT
*/

void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstadd_back(t_list **alst, t_list *new);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
int					ft_isascii (int c);
int					ft_isalpha(int c);
int					ft_isdigit (int c);
int					ft_isalnum (int c);
int					ft_isprint(int c);
size_t				ft_strlen (const char *str);
char				*ft_strdup (const char *s1);
int					ft_strncmp (const char *s1, const char *s2, size_t size);
char				*fstrchr (const char *s, int c);
char				*ft_strrchr (const char *s, int c);
char				*ft_strnstr (const char *haystack, const char *needle,
					size_t len);
size_t				ft_strlcpy (char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_toupper (int c);
int					ft_tolower (int c);
void				*ft_calloc (size_t count, size_t size);
void				*ft_memmove (void *dst, const void *src, size_t len);
void				*ft_memset (void *b, int c, size_t len);
void				*ft_memccpy (void *dst, const void *src, int c, size_t n);
void				*ft_memcpy (void *dst, const void *src, size_t n);
void				*ft_memchr (const void *s, int c, size_t n);
int					ft_memcmp (const void *s1, const void *s2, size_t n);
void				ft_putchar_fd (char c, int fd);
void				ft_putchar (char c);
void				ft_putstr_fd (char *s, int fd);
void				ft_putstr(char *s);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr(int n);
void				ft_putendl_fd(char *s, int fd);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strcpy(char *dest, char *src);
char				*ft_strncpy(char *dest, char *src, unsigned int n);
char				*ft_itoa_base(int nbr, int base);
char				*ft_strlowcase(char *str);
char				*ft_strupcase(char *str);
char				*ft_strlowcase(char *str);
void				*ft_toomuch_read(char *memory, int i);
char				*memorywork(char **line, char *memory);
int					get_next_line(int fd, char **line);
char				*ft_strstr(char *str, char *to_find);
char				*ft_strcat(char *dest, char *src);
/*
** PERSONNELLES
*/

void				ft_read_tab_char(char **tab);
char				*ft_alloc_int(int size);
char				*ft_alloc_char(int size);
float				ft_power(float nb, int power);
int					mini_printf(const char *s, ...);
int					mini_printf_fd(int fd, const char *s, ...);
char				*ft_strtrim_char(char const *s1, char set);
int					ft_isnumber(char *s);
char				*ft_strjoinfree(char const *s1, char const *s2);
int					ft_putchar_return(char c);
int					ft_putstr_return(char *str);
char				*ft_itoa_base_unsigned(unsigned int nombre, int base);
char				*itoa_base_pointeur (void *p);
char				**duplicate_tab_char(char **envp);
void				free_tab_char(char **tab);
int					lenght_double_tab(char **tab);

#endif
