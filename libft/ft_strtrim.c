/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:22 by ibennaje          #+#    #+#             */
/*   Updated: 2024/11/06 15:15:24 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checksep(char sep, char *sets)
{
	while (*sets)
	{
		if (*sets == sep)
			return (1);
		sets++;
	}
	return (0);
}

static unsigned int	ft_start(const char *s1, char *set)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && checksep(s1[i], set))
		i++;
	return (i);
}

static unsigned int	ft_end(const char *s1, char *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i >= 0 && checksep(s1[i], set))
		i--;
	return ((unsigned int)i);
}

static int	onlysep(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (!checksep((char)s1[i], (char *)set))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			len;
	unsigned int	start;
	unsigned int	end;
	char			*trimed;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	if (onlysep(s1, set) || !*s1)
		return (ft_strdup(""));
	start = ft_start(s1, (char *)set);
	end = ft_end(s1, (char *)set);
	len = end - start + 1;
	trimed = ft_substr(s1, start, len);
	return (trimed);
}
