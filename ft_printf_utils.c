/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 21:19:18 by schetty           #+#    #+#             */
/*   Updated: 2021/10/02 21:09:46 by schetty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	util_getpad(t_tab *tab, int len, int has_sgn)
{
	if (tab->is_neg && has_sgn)
		tab->sgn = '-';
	else if (tab->pls && has_sgn)
		tab->sgn = '+';
	else if (tab->spc && has_sgn)
		tab->sgn = ' ';
	if (tab->zro && !tab->pcs)
	{
		tab->pcs = tab->wdt;
		if (tab->sgn)
			tab->pcs -= 1;
	}
	if (tab->pcs > len)
		return (tab->pcs - len);
	else
		return (0);
}

void	util_getwdt(t_tab *tab, int len, int pad)
{
	if (tab->wdt > (len + pad))
	{
		tab->wdt -= (len + pad);
		if (tab->wdt && tab->sgn)
			tab->wdt -= 1;
	}
	else
		tab->wdt = 0;
}

void	util_putnbr(t_tab *tab, unsigned long num, int base, const char *str)
{
	if (num / base)
		util_putnbr(tab, num / base, base, str);
	tab->len += write(1, &str[num % base], 1);
}
