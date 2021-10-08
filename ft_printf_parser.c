/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:33:27 by schetty           #+#    #+#             */
/*   Updated: 2021/10/02 22:53:24 by schetty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_c(t_tab *tab, int chr)
{
	tab->pcs = 1;
	if (tab->wdt > tab->pcs)
		tab->wdt -= tab->pcs;
	else
		tab->wdt = 0;
	while (!tab->mns && tab->wdt--)
		tab->len += write(1, " ", 1);
	tab->len += write(1, &chr, tab->pcs);
	while (tab->mns && tab->wdt--)
		tab->len += write(1, " ", 1);
}

void	parse_s(t_tab *tab, char *str)
{
	int	len;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (!tab->dot || (tab->dot && tab->pcs > len))
		tab->pcs = len;
	if (tab->wdt > tab->pcs)
		tab->wdt -= tab->pcs;
	else
		tab->wdt = 0;
	while (!tab->mns && tab->wdt--)
		tab->len += write(1, " ", 1);
	tab->len += write(1, str, tab->pcs);
	while (tab->mns && tab->wdt--)
		tab->len += write(1, " ", 1);
}

void	parse_p(t_tab *tab, unsigned long num, const char *str)
{
	int	len;
	int	base;

	base = ft_strlen(str);
	len = ft_intlen_base(num, base) + 2;
	if (tab->wdt > len)
		tab->wdt -= len;
	else
		tab->wdt = 0;
	while (!tab->mns && tab->wdt--)
		tab->len += write(1, " ", 1);
	if (num != 0)
	tab->len += write(1, "0x", 2);
	util_putnbr(tab, num, base, str);
	while (tab->mns && tab->wdt--)
		tab->len += write(1, " ", 1);
}

void	parse_di(t_tab *tab, int num, const char *str)
{
	long long	nbr;
	int			len;
	int			pad;
	int			base;

	base = ft_strlen(str);
	nbr = ft_abs(num);
	if (num < 0)
		tab->is_neg = 1;
	if (tab->dot && !nbr)
		len = 0;
	else
		len = ft_intlen_base(nbr, base);
	pad = util_getpad(tab, len, 1);
	util_getwdt(tab, len, pad);
	while (!tab->mns && tab->wdt--)
		tab->len += write(1, " ", 1);
	if (tab->sgn)
		tab->len += write(1, &tab->sgn, 1);
	while (pad--)
		tab->len += write(1, "0", 1);
	if (len)
		util_putnbr(tab, nbr, base, str);
	while (tab->mns && tab->wdt--)
		tab->len += write(1, " ", 1);
}

void	parse_ux(t_tab *tab, unsigned int num, const char *str, char *ppd)
{
	int	len;
	int	pad;
	int	base;

	base = ft_strlen(str);
	if (tab->dot && !num)
		len = 0;
	else
		len = ft_intlen_base(num, base);
	if (num && tab->hsh)
		len += ft_strlen(ppd);
	pad = util_getpad(tab, len, 0);
	util_getwdt(tab, len, pad);
	while (!tab->mns && tab->wdt--)
		tab->len += write(1, " ", 1);
	while (pad--)
		tab->len += write(1, "0", 1);
	if (len)
	{
		if (num && tab->hsh)
			tab->len += write(1, ppd, 2);
		util_putnbr(tab, num, base, str);
	}
	while (tab->mns && tab->wdt--)
		tab->len += write(1, " ", 1);
}
