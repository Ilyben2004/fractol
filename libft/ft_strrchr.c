/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:15:37 by ibennaje          #+#    #+#             */
/*   Updated: 2024/11/06 15:15:38 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	cc;

	i = ft_strlen(s) - 1;
	cc = c;
	if (cc == 0)
		return ((char *)s + i + 1);
	while (i >= 0)
	{
		if ((unsigned char)s[i] == cc)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
