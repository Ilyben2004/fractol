#include "fractol.h"

void	mandelbort_helper(t_vars *vars, t_compelxes *compelxes)
{
	while (compelxes->n < vars->cords.max_iterations)
	{
		compelxes->z_re2 = compelxes->z_re * compelxes->z_re;
		compelxes->z_im2 = compelxes->z_im * compelxes->z_im;
		if (compelxes->z_re2 + compelxes->z_im2 > 4)
		{
			compelxes->isinside = 0;
			break ;
		}
		compelxes->z_im = 2 * compelxes->z_re * compelxes->z_im
			+ compelxes->c_im;
		compelxes->z_re = compelxes->z_re2 - compelxes->z_im2 + compelxes->c_re;
		compelxes->n++;
	}
}

void	mandelbort_set(t_vars *vars)
{
	t_compelxes	compelxes;

	compelxes.y = -1;
	while (++compelxes.y < vars->cords.image_height)
	{
		compelxes.c_im = vars->cords.max_im - compelxes.y
			* vars->cords.im_helper;
		compelxes.x = -1;
		while (++compelxes.x < vars->cords.image_width)
		{
			compelxes.c_re = vars->cords.min_re + compelxes.x
				* vars->cords.re_helper;
			compelxes.z_re = compelxes.c_re;
			compelxes.z_im = compelxes.c_im;
			compelxes.isinside = 1;
			compelxes.n = 0;
			mandelbort_helper(vars, &compelxes);
			if (!compelxes.isinside)
				img_pix_put(&(vars->fractal.img), compelxes.x, compelxes.y,
					get_color(compelxes.n, vars));
		}
	}
}

void	julia_set(t_vars *vars)
{
	t_compelxes	compelxes;

	compelxes.c_re = vars->cords.julia_reel;
	compelxes.c_im = vars->cords.julia_img;
	compelxes.y = -1;
	while (++compelxes.y < vars->cords.image_height)
	{
		compelxes.x = -1;
		while (++compelxes.x < vars->cords.image_width)
		{
			compelxes.z_re = vars->cords.min_re + compelxes.x
				* vars->cords.re_helper;
			compelxes.z_im = vars->cords.max_im - compelxes.y
				* vars->cords.im_helper;
			compelxes.isinside = 1;
			compelxes.n = 0;
			mandelbort_helper(vars, &compelxes);
			if (!compelxes.isinside)
				img_pix_put(&(vars->fractal.img), compelxes.x, compelxes.y,
					get_color(compelxes.n, vars));
		}
	}
}

void	perpendicular_helper(t_vars *vars, t_compelxes *compelxes)
{
	double	z_re_temp;

	while (compelxes->n < vars->cords.max_iterations)
	{
		compelxes->z_re2 = compelxes->z_re * compelxes->z_re;
		compelxes->z_im2 = compelxes->z_im * compelxes->z_im;
		if (compelxes->z_re2 + compelxes->z_im2 > 4)
		{
			compelxes->isinside = 0;
			break ;
		}
		z_re_temp = compelxes->z_re;
		compelxes->z_re = (compelxes->z_re2 - compelxes->z_im2)
			+ compelxes->c_re;
		compelxes->z_im = -2.0 * fabs(z_re_temp) * compelxes->z_im
			+ compelxes->c_im;
		compelxes->n++;
	}
}

void	perpendicular_set(t_vars *vars)
{
	t_compelxes	compelxes;

	compelxes.y = -1;
	while (++compelxes.y < vars->cords.image_height)
	{
		compelxes.c_im = vars->cords.max_im - compelxes.y
			* vars->cords.im_helper;
		compelxes.x = -1;
		while (++compelxes.x < vars->cords.image_width)
		{
			compelxes.c_re = vars->cords.min_re + compelxes.x
				* vars->cords.re_helper;
			compelxes.z_re = 0;
			compelxes.z_im = 0;
			compelxes.isinside = 1;
			compelxes.n = 0;
			perpendicular_helper(vars, &compelxes);
			if (!compelxes.isinside)
				img_pix_put(&(vars->fractal.img), compelxes.x, compelxes.y,
					get_color(compelxes.n, vars));
		}
	}
}
