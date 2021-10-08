/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 07:09:50 by schetty           #+#    #+#             */
/*   Updated: 2021/10/02 21:14:48 by schetty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_tab(t_tab *tab, int is_reset)
{
	tab->zro = 0;
	tab->hsh = 0;
	tab->mns = 0;
	tab->spc = 0;
	tab->pls = 0;
	tab->dot = 0;
	tab->wdt = 0;
	tab->pcs = 0;
	tab->sgn = '\0';
	tab->is_neg = 0;
	if (is_reset)
		tab->len = 0;
}

static int	is_type(char c)
{
	const char	*str;

	str = "cspdiuxX%";
	while (*str)
	{
		if (c == *str++)
			return (1);
	}
	return (0);
}

static void	eval_nontype(char c, t_tab *tab)
{
	if (ft_isdigit(c))
	{
		if (tab->dot)
			tab->pcs = (tab->pcs * 10) + (c - '0');
		else if (c == '0' && !tab->wdt)
			tab->zro = 1;
		else
			tab->wdt = (tab->wdt * 10) + (c - '0');
	}
	else if (c == '-')
		tab->mns = 1;
	else if (c == '+')
		tab->pls = 1;
	else if (c == ' ')
		tab->spc = 1;
	else if (c == '.')
		tab->dot = 1;
	else if (c == '#')
		tab->hsh = 1;
}

static char	*eval_params(char *param, t_tab *tab)
{
	const char	*dec = "0123456789";
	const char	*lhex = "0123456789abcdef";
	const char	*uhex = "0123456789ABCDEF";

	while (*param && !is_type(*param))
		eval_nontype(*param++, tab);
	if (*param == 'c')
		parse_c(tab, va_arg(tab->arg, int));
	else if (*param == 's')
		parse_s(tab, va_arg(tab->arg, char *));
	else if (*param == 'p')
		parse_p(tab, va_arg(tab->arg, unsigned long), lhex);
	else if (*param == 'd' || *param == 'i')
		parse_di(tab, va_arg(tab->arg, int), dec);
	else if (*param == 'u')
		parse_ux(tab, va_arg(tab->arg, unsigned int), dec, "");
	else if (*param == 'x')
		parse_ux(tab, va_arg(tab->arg, unsigned int), lhex, "0x");
	else if (*param == 'X')
		parse_ux(tab, va_arg(tab->arg, unsigned int), uhex, "0X");
	else if (*param == '%')
		tab->len += write(1, "%", 1);
	return (++param);
}

int	ft_printf(const char *param, ...)
{
	t_tab	*tab;
	int		ret;

	tab = malloc(sizeof(t_tab));
	if (!tab)
		return (-1);
	init_tab(tab, 1);
	ret = 0;
	va_start(tab->arg, param);
	while (*param)
	{
		if (*param == '%' && *param++)
		{
			param = eval_params((char *)param, tab);
			init_tab(tab, 0);
		}
		else
			ret += write(1, param++, 1);
	}
	va_end(tab->arg);
	ret += tab->len;
	free(tab);
	return (ret);
}
