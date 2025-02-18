#include "fractol.h"

void mandelbort_helper(t_vars *vars, t_compelxes *compelxes)
{
	while (compelxes->n < vars->cords.MaxIterations)
	{
		compelxes->z_re2 = compelxes->z_re * compelxes->z_re;
		compelxes->z_im2 = compelxes->z_im * compelxes->z_im;
		if (compelxes->z_re2 + compelxes->z_im2 > 4)
		{
			compelxes->isinside = 0;
			break;
		}
		compelxes->z_im = 2 * compelxes->z_re * compelxes->z_im + compelxes->c_im;
		compelxes->z_re = compelxes->z_re2 - compelxes->z_im2 + compelxes->c_re;
		vars->cords.color = compelxes->n;
		compelxes->n++;
	}
}

void mandelbort_set(t_vars *vars)
{
	t_compelxes compelxes;
	compelxes.y = -1;

	while (++compelxes.y < vars->cords.ImageHeight)
	{
		compelxes.c_im = vars->cords.MaxIm - compelxes.y * vars->cords.Im_factor;
		compelxes.x = -1;
		while (++compelxes.x < vars->cords.ImageWidth)
		{
			compelxes.c_re = vars->cords.MinRe + compelxes.x * vars->cords.Re_factor;
			compelxes.z_re = compelxes.c_re;
			compelxes.z_im = compelxes.c_im;
			compelxes.isinside = 1;
			compelxes.n = 0;
			mandelbort_helper(vars, &compelxes);
			if (!compelxes.isinside)
				img_pix_put(&(vars->fractal.img), compelxes.x, compelxes.y, get_color(vars->cords.color));
		}
	}
}

void julia_set(t_vars *vars)
{
	t_compelxes compelxes;
	compelxes.c_re = -0.7;
	compelxes.c_im = 0.27015;

	compelxes.y = -1;

	while (++compelxes.y < vars->cords.ImageHeight)
	{
		compelxes.x = -1;
		while (++compelxes.x < vars->cords.ImageWidth)
		{
			compelxes.z_re = vars->cords.MinRe + compelxes.x * vars->cords.Re_factor;
			compelxes.z_im = vars->cords.MaxIm - compelxes.y * vars->cords.Im_factor;
			compelxes.isinside = 1;
			compelxes.n = 0;
			mandelbort_helper(vars, &compelxes);
			if (!compelxes.isinside)
				img_pix_put(&(vars->fractal.img), compelxes.x, compelxes.y, get_color(vars->cords.color));
		}
	}
}

void perpendicular_set(t_vars *vars)
{
	t_compelxes complexes;

	complexes.y = 0;
	while (complexes.y < vars->cords.ImageHeight)
	{
		complexes.c_im = vars->cords.MaxIm - complexes.y * vars->cords.Im_factor;
		complexes.x = 0;
		while (complexes.x < vars->cords.ImageWidth)
		{
			complexes.c_re = vars->cords.MinRe + complexes.x * vars->cords.Re_factor;

			complexes.z_re = vars->cords.MinRe + complexes.x * vars->cords.Re_factor;
			complexes.z_im = vars->cords.MaxIm - complexes.y * vars->cords.Im_factor;
			complexes.n = 0;
			complexes.isinside = 1;

			while (complexes.n < vars->cords.MaxIterations)
			{
				complexes.z_re2 = complexes.z_re * complexes.z_re;
				complexes.z_im2 = complexes.z_im * complexes.z_im;
				if (complexes.z_re2 + complexes.z_im2 > 4)
				{
					complexes.isinside = 0;
					break;
				}
				complexes.z_im = 2 * complexes.z_re * complexes.z_im + complexes.c_im;
				complexes.z_re = complexes.z_re2 - complexes.z_im2 + complexes.c_re;
				vars->cords.color = complexes.n;
				complexes.n++;
			}
			if (complexes.isinside)
				img_pix_put(&(vars->fractal.img), complexes.x, complexes.y, 0x000000);
			else
				img_pix_put(&(vars->fractal.img), complexes.x, complexes.y, get_color(complexes.n));
			complexes.x++;
		}
		complexes.y++;
	}
}