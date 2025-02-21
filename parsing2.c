#include "fractol.h"

int	ft_free(char *is_float, char *intpart)
{
	if (is_float)
		free(intpart);
	return (1);
}

void	error_exit(void)
{
	const char	*errmsg;
	int			i;

	i = 0;
	errmsg = "********************** ibennaje fractol **********************\n"
		"available fractals are : mandelbrot julia perpendicular\n"
		"you only can do : ./fractol mandelbrot || ./fractol perpendicular"
		"|| ./fractol julia\n"
		"you have the option to give julia 2 parameters as number like :\n"
		"./fractol julia xx.xxxxxxxxxx xx.xxxxxxxxxx\n"
		"note that the decimal part only defined between 2 and -2\n";
	while (errmsg[i])
		write(1, &errmsg[i++], 1);
	exit(0);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	is_number(char *num)
{
	char	*is_float;
	char	*intpart;
	int		i;

	i = 0;
	if (!*num || num[ft_strlen(num) - 1] == '.')
		error_exit();
	if (num[i] == '+' || num[i] == '-')
		i++;
	is_float = ft_strchr(num, '.');
	while (num[i++])
		if (!ft_isdigit(num[i - 1]) && &num[i - 1] != is_float)
			error_exit();
	if (is_float)
		intpart = ft_substr(num, 0, is_float - num);
	else
		intpart = num;
	if (ft_strlen(intpart) > 2 || ft_atoi(intpart) > 2 || ft_atoi(intpart) < -2)
	{
		if (is_float)
			free(intpart);
		error_exit();
	}
	return (ft_free(is_float, intpart));
}

int	number_len(long number)
{
	int	i;

	i = 0;
	while (number != 0)
	{
		i++;
		number /= 10;
	}
	return (i);
}
