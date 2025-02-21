#include "fractol.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	cc;

	cc = c;
	i = 0;
	if (cc == 0)
		return ((char *)s + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

long	ft_atoi(const char *str)
{
	int		sign;
	size_t	result;

	result = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	char	*ss;

	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	ss = (char *)s;
	i = 0;
	while (i < len && ss[start])
	{
		substr[i++] = ss[start++];
	}
	substr[i] = '\0';
	return (substr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
