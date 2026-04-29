/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakemur <ttakemur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 06:14:16 by ttakemur          #+#    #+#             */
/*   Updated: 2026/04/30 02:49:14 by ttakemur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_specifier(va_list ap, char spec)
{
	if (spec == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (spec == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (spec == 'd' || spec == 'i')
		return (ft_putnbr(va_arg(ap, int)));
	else if (spec == 'u')
		return (ft_putunsigned(va_arg(ap, int)));
	else if (spec == 'x' || spec == 'X')
		return (ft_puthex((unsigned long)va_arg(ap, unsigned int),
				spec == 'X'));
	else if (spec == 'p')
		return (ft_putptr(va_arg(ap, void *)));
	else if (spec == '%')
		return (ft_putchar('%'));
	else
		return (ft_putchar('%') + ft_putchar(va_arg(ap, int)));
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, fmt);
	count = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			count += ft_handle_specifier(ap, *fmt);
		}
		else
			count += ft_putchar(*fmt);
		fmt++;
	}
	va_end(ap);
	return (count);
}
