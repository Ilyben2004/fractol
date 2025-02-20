/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:05:29 by ibennaje          #+#    #+#             */
/*   Updated: 2024/11/06 15:05:30 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s2;
	size_t	size;
	size_t	i;

	size = ft_strlen(s);
	s2 = (char *)malloc(size + 1);
	if (!s2)
		return (NULL);
	i = 0;
	while (i < size)
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}
