/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:31:04 by ibennaje          #+#    #+#             */
/*   Updated: 2024/11/06 15:31:05 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joinstr;
	size_t	s1size;
	size_t	s2size;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1size = ft_strlen(s1);
	s2size = ft_strlen(s2);
	joinstr = (char *)malloc(s1size + s2size + 1);
	if (!joinstr)
		return (NULL);
	ft_memmove(joinstr, s1, s1size);
	ft_memmove(joinstr + s1size, s2, s2size);
	joinstr[s1size + s2size] = '\0';
	return (joinstr);
}
