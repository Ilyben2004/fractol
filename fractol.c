/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <ibennaje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:07:00 by ibennaje          #+#    #+#             */
/*   Updated: 2025/02/17 06:20:48 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct s_img
{
	void *mlx_img;
	char *addr;
	int bpp;
	int line_len;
	int endian;
} t_img;
typedef struct s_fractal
{
	void *mlx;
	void *mlx_win;
	t_img img;

} t_fractal;

typedef struct s_cords
{
	int ImageHeight;
	int ImageWidth;
	double MaxRe;
	double MinRe;
	double MinIm;
	double MaxIm;
	double Re_factor;
	double Im_factor;
	int MaxIterations;
	int color;
	double zoom;
	double cx;
	double cy;

} t_cords;

typedef struct s_compelxes
{
	int x;
	int y;
	int n;
	double z_re;
	double z_im;
	double c_re;
	double c_im;
	double z_re2;
	double z_im2;
	int isinside;

	/* data */
} t_compelxes;

typedef struct s_vars
{
	t_cords cords;
	t_fractal fractal;
	void (*draw)(struct s_vars *vars);
	int ini;
} t_vars;

void img_pix_put(t_img *img, int x, int y, int color)
{
	char *pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int get_color(int iterations)
{
	int offset;

	if (iterations == 0)
		iterations = 1;

	offset = iterations * 100000;
	return (iterations * offset);
}

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

void cords_init(t_cords *cords, int zoomchecker)
{
	if (zoomchecker == 1)
		cords->zoom = 1;
	if (zoomchecker == 4)
		cords->zoom -= 0.1;

	cords->ImageHeight = 600;
	cords->ImageWidth = 600;
	cords->MaxRe = 2.0;
	cords->MinRe = -2.0;
	cords->MinIm = -2.0;
	cords->MaxIm = 2.0;
	cords->cx = 0;
	cords->cy = 0;
	cords->Re_factor = (cords->MaxRe - cords->MinRe) / (cords->ImageWidth - 1);
	cords->Im_factor = (cords->MaxIm - cords->MinIm) / (cords->ImageHeight - 1);
	cords->MaxIterations = 100;
}

void range_zoom_calculator(int keycode, double *range_re, double *range_im, t_vars *vars)
{
	double zoom = 1.1;
	if (keycode == 4)
	{
		*range_re = (vars->cords.MaxRe - vars->cords.MinRe) / zoom;
		*range_im = (vars->cords.MaxIm - vars->cords.MinIm) / zoom;
	}
	else
	{
		*range_re = (vars->cords.MaxRe - vars->cords.MinRe) * zoom;
		*range_im = (vars->cords.MaxIm - vars->cords.MinIm) * zoom;
	}
	vars->cords.MinRe = vars->cords.cx - ((*range_re) / 2);
	vars->cords.MaxRe = vars->cords.cx + ((*range_re) / 2);
	vars->cords.MinIm = vars->cords.cy - ((*range_im) / 2);
	vars->cords.MaxIm = vars->cords.cy + ((*range_im) / 2);
	vars->cords.Re_factor = ((vars->cords.MaxRe - vars->cords.MinRe) / (vars->cords.ImageWidth - 1));
	vars->cords.Im_factor = ((vars->cords.MaxIm - vars->cords.MinIm) / (vars->cords.ImageHeight - 1));
}

int zoom(int keycode, int x, int y, t_vars *vars)
{
	double range_re;
	double range_im;
	void *old_image;

	if (keycode == 4 || keycode == 5)
	{
		range_zoom_calculator(keycode, &range_re, &range_im, vars);
		old_image = vars->fractal.img.mlx_img;
		vars->fractal.img.mlx_img = mlx_new_image(vars->fractal.mlx, vars->cords.ImageWidth, vars->cords.ImageHeight);
		vars->fractal.img.addr = mlx_get_data_addr(vars->fractal.img.mlx_img,
												   &vars->fractal.img.bpp, &vars->fractal.img.line_len,
												   &vars->fractal.img.endian);
		if (old_image)
			mlx_destroy_image(vars->fractal.mlx, old_image);
		vars->draw(vars);
		mlx_put_image_to_window(vars->fractal.mlx, vars->fractal.mlx_win,
								vars->fractal.img.mlx_img, 0, 0);
	}
}

int destroy_window(t_vars *vars)
{
	mlx_destroy_image(vars->fractal.mlx, vars->fractal.img.mlx_img);
	mlx_destroy_window(vars->fractal.mlx, vars->fractal.mlx_win);
}
int key_hook_helper(t_vars *vars, int keycode)
{
	if (keycode == 65363)
	{
		vars->cords.MinRe += (vars->cords.MaxRe - vars->cords.MinRe) / 20;
		vars->cords.MaxRe += (vars->cords.MaxRe - vars->cords.MinRe) / 20;
		return (1);
	}
	else if (keycode == 65361)
	{
		vars->cords.MinRe -= (vars->cords.MaxRe - vars->cords.MinRe) / 20;
		vars->cords.MaxRe -= (vars->cords.MaxRe - vars->cords.MinRe) / 20;
		return (1);
	}
	else if (keycode == 65362)
	{
		vars->cords.MinIm += (vars->cords.MaxIm - vars->cords.MinIm) / 20;
		vars->cords.MaxIm += (vars->cords.MaxIm - vars->cords.MinIm) / 20;
		return (1);
	}
	else if (keycode == 65364)
	{
		vars->cords.MinIm -= (vars->cords.MaxIm - vars->cords.MinIm) / 20;
		vars->cords.MaxIm -= (vars->cords.MaxIm - vars->cords.MinIm) / 20;
		return (1);
	}
	return (0);
}

int key_hook(int keycode, t_vars *vars)
{
	void *old_image;

	if (key_hook_helper(vars, keycode))
	{
		vars->cords.cx = (vars->cords.MaxRe + vars->cords.MinRe) / 2;
		vars->cords.cy = (vars->cords.MaxIm + vars->cords.MinIm) / 2;

		old_image = vars->fractal.img.mlx_img;
		vars->fractal.img.mlx_img = mlx_new_image(vars->fractal.mlx, vars->cords.ImageWidth, vars->cords.ImageHeight);
		vars->fractal.img.addr = mlx_get_data_addr(vars->fractal.img.mlx_img,
												   &vars->fractal.img.bpp, &vars->fractal.img.line_len,
												   &vars->fractal.img.endian);
		if (old_image)
			mlx_destroy_image(vars->fractal.mlx, old_image);
		vars->draw(vars);
		mlx_put_image_to_window(vars->fractal.mlx, vars->fractal.mlx_win,
								vars->fractal.img.mlx_img, 0, 0);
	}
	else if (keycode == 65307)
	{
		destroy_window(vars);
		exit(0);
	}
	return (1);
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

            complexes.z_re = 0;
            complexes.z_im = 0;
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
                double z_re_temp = complexes.z_re;
                complexes.z_re = (complexes.z_re2 - complexes.z_im2) + complexes.c_re;
                complexes.z_im = -2.0 * fabs(z_re_temp) * complexes.z_im + complexes.c_im;
                vars->cords.color = complexes.n;
                complexes.n++;
            }
            if (complexes.isinside)
                img_pix_put(&(vars->fractal.img), complexes.x, complexes.y, 0x000000);
            else
                img_pix_put(&(vars->fractal.img), complexes.x, complexes.y, get_color(vars->cords.color));
            complexes.x++;
        }
        complexes.y++;
    }
}

int main(int ac, char **av)
{
	t_vars vars;

	if (strcmp(av[1], "mandelbrot") == 0)
		vars.draw = mandelbort_set;
	if (strcmp(av[1], "julia") == 0)
		vars.draw = julia_set;
	vars.draw = perpendicular_set;
	vars.fractal.mlx = mlx_init();
	vars.fractal.mlx_win = mlx_new_window(vars.fractal.mlx, 600, 600, "Julia Set");
	cords_init(&vars.cords, 1);
	vars.fractal.img.mlx_img = mlx_new_image(vars.fractal.mlx, vars.cords.ImageWidth, vars.cords.ImageHeight);
	vars.fractal.img.addr = mlx_get_data_addr(vars.fractal.img.mlx_img, &vars.fractal.img.bpp, &vars.fractal.img.line_len, &vars.fractal.img.endian);
	vars.draw(&vars);
	vars.ini = 1;
	mlx_put_image_to_window(vars.fractal.mlx, vars.fractal.mlx_win, vars.fractal.img.mlx_img, 0, 0);
	mlx_mouse_hook(vars.fractal.mlx_win, &zoom, &vars);
	mlx_hook(vars.fractal.mlx_win, 17, 0, destroy_window, &vars);
	mlx_key_hook(vars.fractal.mlx_win, key_hook, &vars);
	mlx_loop(vars.fractal.mlx);
}
