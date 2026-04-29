/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakemur <ttakemur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 06:13:16 by ttakemur          #+#    #+#             */
/*   Updated: 2026/04/30 02:49:57 by ttakemur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned long n, int upper)
{
	char	*hex;
	size_t	count;

	if (upper)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	count = 0;
	if (n >= 16)
		count += ft_puthex(n >> 4, upper);
	count += ft_putchar(hex[n & 0xf]);
	return (count);
}
