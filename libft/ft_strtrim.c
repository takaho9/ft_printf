/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakemur <ttakemur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:50:08 by ttakemur          #+#    #+#             */
/*   Updated: 2026/04/29 06:24:20 by ttakemur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	flags[256];
	size_t	len;
	char	*trimed;

	ft_bzero(flags, 256);
	while (*set)
	{
		flags[(unsigned char)*set++] = 1;
	}
	while (flags[(unsigned char)*s1])
		s1++;
	len = 0;
	while (s1[len])
	{
		len++;
	}
	while (len != 0 && flags[(unsigned char)s1[len - 1]])
		len--;
	trimed = malloc(sizeof(char) * (len + 1));
	if (trimed == NULL)
		return (NULL);
	ft_memcpy(trimed, s1, len);
	trimed[len] = '\0';
	return (trimed);
}
