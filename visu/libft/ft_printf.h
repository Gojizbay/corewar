/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/21 16:57:59 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 10:33:00 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <wchar.h>
# include <locale.h>
# include "libft.h"
# define ATTRIB "0- +#"
# define INDIC "scpdiouxXbSCDOU%"
# define TAILLE "hhlljz"

typedef struct		s_spec
{
	char			*attrib;
	int				largmin;
	int				precis;
	int				isprec;
	char			*taille;
	char			indic;
	int				len;
	char			*buf;
	int				index;
	int				ret;
	int				wclarg;
	int				wcprec;
}					t_spec;

void				ft_putstr(char const *s);
void				ft_putchar(char c);
int					ft_nblen(intmax_t nb);
int					ft_unblen(unsigned long long nb);
char				*ft_utoa_base(uintmax_t value, int base, char *taille);
int					ft_atoi(const char *str);
int					pf_countchar(const char *s, char c);
int					ft_charpos(char *str, char c);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strnew(size_t size);
int					pf_strlen(const char *s);
char				*pf_itoa(intmax_t nb);
void				pf_putnbr(intmax_t nb);
void				ft_putunbr(unsigned long long nb);
char				*ft_strtoupper(char *s);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strdup(const char *s);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_charstrstr(const char *s1, const char *s2);
void				ft_strdel(char **as);
void				ft_putstrn(const char *str, int len);
void				ft_putstrnw(const wchar_t *str, int len);
void				ft_putwstr(wchar_t *s);
int					ft_wstrlen(const wchar_t *s);
char				*pf_strjoin(char *s1, char *s2);

int					ft_printf(const char *format, ...);
t_spec				*ft_fill_struct(char *str);
void				ft_initialize_struct(t_spec *sp);
int					ft_indicchar(t_spec *sp, void *arg);
int					ft_indiclong(t_spec *sp, intmax_t arg);
int					ft_attributs(t_spec *sp, intmax_t arg, int len);
int					ft_largmin(t_spec *sp, int len, intmax_t arg);
int					ft_largminstr(t_spec *sp, int len);
int					isattrib(char *s);
int					isindic(char c);
int					isindicint(char c);
int					calcistring(t_spec *sp, void *arg, int len);
int					ft_precision(t_spec *sp, int len, intmax_t arg);
int					ft_precisionbigs(t_spec *sp, wchar_t *arg);
int					ft_taille(t_spec *sp, intmax_t arg);
void				ft_putwchar(wchar_t w);
int					sizeofwchar(wchar_t w);
int					checkmcm(wchar_t *s, int len);
uintmax_t			goodcast(intmax_t nbr, char *taille);
void				structdel(t_spec *sp);
void				init_tab(int *tab);

int					ft_s(t_spec *sp, void *arg);
int					ft_uppers(t_spec *sp, void *arg);
int					ft_p(t_spec *sp, intmax_t arg);
int					ft_d(t_spec *sp, intmax_t arg);
int					ft_upperd(t_spec *sp, void *arg);
int					ft_i(t_spec *sp, intmax_t arg);
int					ft_o(t_spec *sp, intmax_t arg);
int					ft_uppero(t_spec *sp, void *arg);
int					ft_u(t_spec *sp, intmax_t arg);
int					ft_upperu(t_spec *sp, void *arg);
int					ft_x(t_spec *sp, intmax_t arg);
int					ft_upperx(t_spec *sp, intmax_t arg);
int					ft_c(t_spec *sp, intmax_t arg);
int					ft_upperc(t_spec *sp, intmax_t arg);
int					ft_b(t_spec *sp, intmax_t arg);
int					ft_mod(t_spec *sp, intmax_t arg);
void				ft_n(t_spec *sp, intmax_t *arg, int ret);

int					ft_sharp(t_spec *sp, intmax_t arg, int len);
int					ft_zero(t_spec *sp, intmax_t arg, int len);
int					ft_space(t_spec *sp, intmax_t arg, int len);
int					ft_plus(t_spec *sp, intmax_t arg, int len);

#endif
