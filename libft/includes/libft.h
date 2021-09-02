/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:57:03 by edjubert          #+#    #+#             */
/*   Updated: 2019/08/11 17:17:20 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define BUFF_SIZE_GNL	32

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_lprintf
{
	char				*special;
	char				*field;
	char				*precision;
	char				*dpp;
	char				*modifier;
	char				*conversion;
	char				*percent;
	char				*to_swap;
	void				*arg;
	int					fd;
	int					error;
	double				f;
	long double			lf;
	struct s_lprintf	*next;
}				t_lprintf;

/*
** FT_PRINTF PROTOTYPES
*/

int				ft_printf(const char *restrict format, ...);
int				ft_init(char *percent, t_lprintf **list, void *arg);
int				ft_init_float(char *percent,
	t_lprintf **list, double args);
int				ft_init_float_long(char *percent,
	t_lprintf **list, long double args);
void			handle_char(t_lprintf *list);
void			handle_binary(t_lprintf *list);
void			handle_string(t_lprintf *list);
void			handle_digit(t_lprintf *list);
void			handle_base(t_lprintf *list);
void			handle_long(t_lprintf *list);
void			handle_hexa_long(t_lprintf *list);
void			handle_float(t_lprintf *list);
void			handle_float_long(t_lprintf *list);
void			handle_octal_long(t_lprintf *list);
void			handle_padding(t_lprintf *list);
void			handle_unsigned(t_lprintf *list);
void			handle_unsigned_long(t_lprintf *list);
void			padd_digit(t_lprintf **list, char *arg, int field, int left);
void			print_field(int field, t_lprintf **list);
int				ft_parse(t_lprintf **list, char *str);
void			ft_check(t_lprintf **list);
int				ft_choose(char *str, t_lprintf **list);
int				ft_color(char *str, t_lprintf **list, int start);
t_lprintf		*ft_create_argument_list(void);
void			ft_lst_del(t_lprintf **list);
void			handle_padding(t_lprintf *list);
void			handle_title(t_lprintf *list);
void			ft_add(char c, char ***title);
void			ft_add_pqr(char c, char ***title);
int				ft_strlen_swap(t_lprintf *list);
unsigned char	*handle_unicode(wchar_t unicode);
int				ft_strlenuni(wchar_t *str);
int				ft_25line(char c);

/*
**	LIBFT PROTOTYPES
*/

void			ft_strirep(unsigned char *dst, unsigned char *src, size_t index,
					size_t plen);
int				ft_abs(int nb);
int				ft_atoi(const char *str);
long			ft_atol(const char *str);
unsigned long	ft_atoul(const char *str);
int				ft_bindec(char *bin);
void			ft_bzero(void *s, size_t n);
int				get_next_line(const int fd, char **line);
double			ft_dabs(double n);
char			*ft_dtob(double val);
int				ft_dneg(double val);
int				ft_intlen(long long int n);
int				ft_intlen_unsigned(unsigned long long int n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isword(int i, const char *s, char c);
char			*ft_itoa(long long int n);
char			*ft_itoa_base(int value, int base, int capital);
char			*ft_itoa_long(long int n);
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstqueue(t_list **alst, t_list *new);
void			*ft_memalloc(size_t size);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_memdel(void **ap);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
double			ft_pow(double n, int pow);
void			ft_putchar_fd(char c, int fd);
void			ft_putchar(char c);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putendl(char const *s);
void			ft_putnbr_fd(int n, int fd);
void			ft_putnbr(int n);
void			ft_putstr_fd(char const *str, int fd);
void			ft_putstr(char *str);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
void			ft_strclr(char *s);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
void			ft_strdel(char **as);
char			*ft_strdup(const char *s1);
char			*ft_strldup(const char *s1, size_t n);
int				ft_strequ(char const *s1, char const *s2);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin_free(char *s1, char *s2, int mode);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen_pro(const char *s);
size_t			ft_strlen_free(char *s);
size_t			ft_strlen(const char *s);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *s1, const char *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t len);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *haystack,
	const char *needle, size_t len);
char			*ft_strrchr(const char *s, int c);
void			ft_strrev(char *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strsub_free(char *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_utoa_long(unsigned long long int n);
char			*ft_utoa_base(u_int64_t value, int base, int capital);
int				ft_wlen(const char *s, int i, char c);
int				ft_sqrt(int nbr);
int				ft_lstsize(t_list *als);
void			ft_tabdel(char ***tab);
void			ft_swap(void *addr1, void *adrr2);
int				ft_match(char *s1, char *s2);
int				ft_nmatch(char *s1, char *s2);
int				ft_matcha(char *s1, char *s2);
int				ft_count_needles(char *haystack, char *needle);

#endif
