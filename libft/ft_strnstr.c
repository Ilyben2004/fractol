/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:16:32 by ibennaje          #+#    #+#             */
/*   Updated: 2024/11/06 15:16:33 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!haystack && len == 0)
		return (NULL);
	if (!needle[0])
		return ((char *)haystack);
	if (ft_strlen(needle) > ft_strlen(haystack))
		return (NULL);
	i = 0;
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[i - i])
		{
			j = i + 1;
			while ((haystack[j] == needle[j - i]) && needle[j - i] && j < len)
				j++;
			if ((!needle[j - i]))
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
