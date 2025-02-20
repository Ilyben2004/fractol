/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:31:56 by ibennaje          #+#    #+#             */
/*   Updated: 2024/11/06 15:32:01 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	nwords;

	nwords = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c && *s != '\0')
		{
			nwords++;
			while (*s && *s != c)
				s++;
		}
	}
	return (nwords);
}

static size_t	word_length(char const *word, char c)
{
	size_t	i;

	i = 0;
	while (word[i] && word[i] != c)
		i++;
	return (i);
}

static void	*ft_free(char **forfree, size_t tozero)
{
	while (tozero > 0)
		free(forfree[--tozero]);
	free(forfree);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	nwords;
	size_t	wordlength;
	size_t	i;
	char	**splited;

	if (!s)
		return (NULL);
	nwords = count_words(s, c);
	splited = (char **)malloc((nwords + 1) * sizeof(char *));
	if (!splited)
		return (NULL);
	i = 0;
	while (i < nwords)
	{
		while (*s == c)
			s++;
		wordlength = word_length(s, c);
		splited[i] = ft_substr(s, 0, wordlength);
		if (!splited[i])
			return (ft_free(splited, i));
		s += wordlength;
		i++;
	}
	splited[i] = NULL;
	return (splited);
}
