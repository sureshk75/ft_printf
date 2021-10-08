/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 10:45:50 by schetty           #+#    #+#             */
/*   Updated: 2021/10/02 21:09:57 by schetty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"

typedef struct s_tab
{
	int		zro;
	int		hsh;
	int		mns;
	int		spc;
	int		pls;
	int		dot;
	int		wdt;
	int		pcs;
	int		len;
	char	sgn;
	int		is_neg;
	va_list	arg;
}			t_tab;

int		ft_printf(const char *param, ...);
void	parse_c(t_tab *tab, int chr);
void	parse_s(t_tab *tab, char *str);
void	parse_p(t_tab *tab, unsigned long num, const char *str);
void	parse_di(t_tab *tab, int num, const char *str);
void	parse_ux(t_tab *tab, unsigned int num, const char *str, char *ppd);
void	util_putnbr(t_tab *tab, unsigned long num, int base, const char *str);
int		util_getpad(t_tab *tab, int len, int has_sgn);
void	util_getwdt(t_tab *tab, int len, int pad);

#endif
