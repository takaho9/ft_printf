/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakemur <ttakemur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:57:58 by ttakemur          #+#    #+#             */
/*   Updated: 2026/04/27 00:17:02 by ttakemur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (!in_word)
		{
			count++;
			in_word = 1;
		}
		s++;
	}
	return (count);
}

static void	*free_words(char **words, size_t j)
{
	while (j > 0)
		free(words[--j]);
	free(words);
	return (NULL);
}

static char	*next_word(char const *s, char c, size_t *i)
{
	size_t	start;

	while (s[*i] == c)
		(*i)++;
	if (!s[*i])
		return (NULL);
	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	return (ft_substr(s, start, *i - start));
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	i;
	size_t	j;

	words = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!words)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		words[j] = next_word(s, c, &i);
		if (!words[j] && s[i])
			return (free_words(words, j));
		if (!words[j])
			break ;
		j++;
	}
	words[j] = NULL;
	return (words);
}
