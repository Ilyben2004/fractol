/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:38:15 by ibennaje          #+#    #+#             */
/*   Updated: 2024/11/06 15:38:17 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;
	size_t	totalsize;

	if (nmemb != 0 && SIZE_MAX / nmemb < size)
		return (NULL);
	totalsize = nmemb * size;
	ret = malloc(totalsize);
	if (!ret)
		return (NULL);
	ft_bzero(ret, totalsize);
	return (ret);
}
