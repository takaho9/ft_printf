/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakemur <ttakemur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 06:14:16 by ttakemur          #+#    #+#             */
/*   Updated: 2026/04/29 06:14:33 by ttakemur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_printf(const char *fmt, ...) {
    va_list ap;
    int count;

    va_start(ap, fmt);

    count = 0;
    while(*fmt) {
        if(*fmt == '%')
        {
            fmt++;
            count += ft_handle_specifier(ap, *fmt);
        }
        else
            count += ft_putchar(*fmt);
        fmt++;
    }
    va_end(ap);
    return count;
}
