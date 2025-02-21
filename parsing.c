#include "fractol.h"

static void	set_double_helper(char *float_part_s, double *d, long int_to_float,
		char *dbl)
{
	int		free_s;
	int		float_len;
	long	float_part;
	int		i;

	i = -1;
	free_s = 0;
	if (ft_strlen(float_part_s) > 10)
	{
		free_s = 1;
		float_part_s = ft_substr(float_part_s, 0, 10);
	}
	while (float_part_s[++i] == '0')
		int_to_float *= 10;
	float_part = ft_atoi(float_part_s + i);
	float_len = number_len(float_part);
	while (float_len-- != 0)
		int_to_float *= 10;
	if (dbl[0] == '-')
		float_part = -float_part;
	*d += ((double)float_part / (double)int_to_float);
	if (free_s)
		free(float_part_s);
}

static void	set_double(double *d, char *dbl)
{
	char	*float_part_s;
	long	int_to_float;

	int_to_float = 1;
	*d = ft_atoi(dbl);
	float_part_s = ft_strchr(dbl, '.');
	if (float_part_s++)
		set_double_helper(float_part_s, d, int_to_float, dbl);
}

static void	julia_number_set(t_vars *vars, char *reel, char *img)
{
	set_double(&(vars->cords.julia_reel), reel);
	set_double(&(vars->cords.julia_img), img);
	if (vars->cords.julia_reel > 2 || vars->cords.julia_reel < -2)
		error_exit();
	if (vars->cords.julia_img > 2 || vars->cords.julia_img < -2)
		error_exit();
}

void	parse(int ac, char **av, t_vars *vars)
{
	if (ac == 1 || ac > 4)
		error_exit();
	else if (ac == 2 && ft_strcmp(av[1], "mandelbrot") == 0)
		vars->draw = mandelbort_set;
	else if (ft_strcmp(av[1], "julia") == 0)
	{
		vars->draw = julia_set;
		if (ac == 2)
		{
			vars->cords.julia_img = 0.35;
			vars->cords.julia_reel = 0.35;
		}
		else if (ac == 4 && is_number(av[2]) && is_number(av[3]))
			julia_number_set(vars, av[2], av[3]);
		else
			error_exit();
	}
	else if (ac == 2 && ft_strcmp(av[1], "perpendicular") == 0)
		vars->draw = perpendicular_set;
	else
		error_exit();
}
