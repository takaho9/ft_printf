/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakemur <ttakemur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:50:08 by ttakemur          #+#    #+#             */
/*   Updated: 2026/04/27 00:34:18 by ttakemur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	buf[12];
	long	num;
	size_t	i;

	buf[11] = '\0';
	ft_memset(buf, (int) '0', 11);
	num = n;
	if (num < 0)
	{
		num = -num;
	}
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
	ft_putstr_fd(buf + i, fd);
}
