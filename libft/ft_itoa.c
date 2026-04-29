/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakemur <ttakemur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:58:05 by ttakemur          #+#    #+#             */
/*   Updated: 2026/04/27 00:34:08 by ttakemur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	buf[11];
	long	num;
	size_t	i;

	ft_memset(buf, (int) '0', 11);
	num = n;
	if (num < 0)
		num = -num;
	i = 10;
	while (num != 0)
	{
		buf[i--] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		buf[i] = '-';
	i = 0;
	while (buf[i] == '0' && i < 10)
		i++;
	return (ft_substr(buf, i, 11 - i));
}
