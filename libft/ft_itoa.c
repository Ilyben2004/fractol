/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:37:06 by ibennaje          #+#    #+#             */
/*   Updated: 2024/11/06 15:37:07 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nsize(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (2);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char	*num;
	size_t	i;
	size_t	isnega;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = nsize(n);
	isnega = 0;
	num = (char *)malloc(i);
	if (!num)
		return (NULL);
	num[--i] = 0;
	if (n < 0)
	{
		isnega = 1;
		num[0] = '-';
		n = -n;
	}
	while (i > isnega)
	{
		num[--i] = (n % 10) + 48;
		n /= 10;
	}
	return (num);
}
