/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:30:18 by ibennaje          #+#    #+#             */
/*   Updated: 2024/11/07 18:29:44 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	startdst;
	size_t	i;

	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (dstlen >= dstsize)
		return (srclen + dstsize);
	startdst = dstlen;
	i = 0;
	while (src[i] && startdst < dstsize - 1)
	{
		dst[startdst++] = src[i++];
	}
	dst[startdst] = 0;
	return (dstlen + srclen);
}
