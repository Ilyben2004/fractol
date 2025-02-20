/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:16:40 by ibennaje          #+#    #+#             */
/*   Updated: 2024/11/07 18:36:41 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	size;
	char	*str;
	size_t	i;

	if (!s || !f)
		return (NULL);
	i = -1;
	size = ft_strlen(s);
	str = (char *)malloc(size + 1);
	if (!str || !f)
		return (NULL);
	while (s[++i])
	{
		str[i] = f(i, s[i]);
	}
	str[i] = 0;
	return (str);
}
