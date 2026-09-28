/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttang <ttang@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by ttang             #+#    #+#             */
/*   Updated: 2026/09/28 00:00:00 by ttang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	**free_words(char **words, size_t count)
{
	while (count > 0)
		free(words[--count]);
	free(words);
	return (NULL);
}

static char	*copy_word(const char *s, size_t len)
{
	char	*word;

	word = malloc(len + 1);
	if (word == NULL)
		return (NULL);
	ft_memcpy(word, s, len);
	word[len] = '\0';
	return (word);
}

static char	**fill_words(char **words, const char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		words[i] = copy_word(s, len);
		if (words[i] == NULL)
			return (free_words(words, i));
		i++;
		s += len;
	}
	words[i] = NULL;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**words;

	count = count_words(s, c);
	if (count > (size_t)-1 / sizeof(char *) - 1)
		return (NULL);
	words = malloc((count + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	return (fill_words(words, s, c));
}
