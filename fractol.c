/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <ibennaje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:07:00 by ibennaje          #+#    #+#             */
/*   Updated: 2025/02/16 17:15:31 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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

typedef struct s_vars
{
	t_cords cords;
	t_fractal fractal;
	int ini;
} t_vars;

void img_pix_put(t_img *img, int x, int y, int color)
{
	char *pixel;
	int i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int get_color(int iterations)
{
	int offset;

	if (iterations == 0)
		iterations =1;

	offset = iterations * 100000;
	return (iterations * offset );
}

void mandelbort_set(t_vars *vars)
{
	int x, y, n;
	y = 0;

	while (y < vars->cords.ImageHeight)
	{
		double c_im = vars->cords.MaxIm - y * vars->cords.Im_factor;
		x = 0;
		while (x < vars->cords.ImageWidth)
		{
			double c_re = vars->cords.MinRe + x * vars->cords.Re_factor;

			double Z_re = c_re, Z_im = c_im;
			int isInside = 1;
			n = 0;
			while (n < vars->cords.MaxIterations)
			{
				double Z_re2 = Z_re * Z_re, Z_im2 = Z_im * Z_im;
				if (Z_re2 + Z_im2 > 4)
				{
					isInside = 0;
					break;
				}
				Z_im = 2 * Z_re * Z_im + c_im;
				Z_re = Z_re2 - Z_im2 + c_re;
				vars->cords.color = n;
				n++;
			}
			if (isInside)
			{

				img_pix_put(&(vars->fractal.img), x, y, 0xffffff);
			}
			else
			{
				img_pix_put(&(vars->fractal.img), x, y, get_color(vars->cords.color));
			}
			x++;
		}
		y++;
	}
}

void julia_set(t_vars *vars)
{
	int x, y, n;
	y = 0;

	while (y < vars->cords.ImageHeight)
	{
		double Z_im = vars->cords.MaxIm - y * vars->cords.Im_factor;
		x = 0;
		while (x < vars->cords.ImageWidth)
		{
			double Z_re = vars->cords.MinRe + x * vars->cords.Re_factor;

			double c_re = 0.35;
			double c_im = 0.35;
			int isInside = 1;
			n = 0;

			while (n < vars->cords.MaxIterations)
			{
				double Z_re2 = Z_re * Z_re, Z_im2 = Z_im * Z_im;
				if (Z_re2 + Z_im2 > 4)
				{
					isInside = 0;
					break;
				}
				Z_im = 2 * Z_re * Z_im + c_im;
				Z_re = Z_re2 - Z_im2 + c_re;
				vars->cords.color = n;
				n++;
			}

			if (isInside)
				img_pix_put(&(vars->fractal.img), x, y, vars->cords.color * 16737894);
			else
			{
				if (vars->cords.color == 0)
					vars->cords.color = 100;
				img_pix_put(&(vars->fractal.img), x, y, vars->cords.color * 50);
			}
			x++;
		}
		y++;
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
	cords->MaxRe = 1.0;
	cords->MinRe = -2.0;
	cords->MinIm = -1.2;
	cords->MaxIm = 1.12;
	cords->cx = 0;
	cords->cy = 0;
	printf("%f \n%f \n%f \n%f \n", cords->MinRe, cords->MaxRe, cords->MinIm, cords->MaxIm);
	cords->Re_factor = ((cords->MaxRe - cords->MinRe) / (cords->ImageWidth - 1));
	cords->Im_factor = ((cords->MaxIm - cords->MinIm) / (cords->ImageHeight - 1));
	cords->MaxIterations = 100;
}

int zoom_in(int keycode, int x, int y, t_vars *vars)
{
	double range_re;
	double range_im;
	double zoom = 1.1;
	void *old_image;

	printf("(%d  , %d) \n", x, y);
	if (keycode == 4 || keycode == 5)
	{
		if (keycode == 4)
		{
			range_re = (vars->cords.MaxRe - vars->cords.MinRe) / zoom;
			range_im = (vars->cords.MaxIm - vars->cords.MinIm) / zoom;
		}
		else
		{
			range_re = (vars->cords.MaxRe - vars->cords.MinRe) * zoom;
			range_im = (vars->cords.MaxIm - vars->cords.MinIm) * zoom;
		}
		vars->cords.MinRe = vars->cords.cx - ((range_re) / 2);
		vars->cords.MaxRe = vars->cords.cx + ((range_re) / 2);
		vars->cords.MinIm = vars->cords.cy - ((range_im) / 2);
		vars->cords.MaxIm = vars->cords.cy + ((range_im) / 2);
		vars->cords.Re_factor = ((vars->cords.MaxRe - vars->cords.MinRe) / (vars->cords.ImageWidth - 1));
		vars->cords.Im_factor = ((vars->cords.MaxIm - vars->cords.MinIm) / (vars->cords.ImageHeight - 1));

		old_image = vars->fractal.img.mlx_img;
		vars->fractal.img.mlx_img = mlx_new_image(vars->fractal.mlx, vars->cords.ImageWidth, vars->cords.ImageHeight);
		vars->fractal.img.addr = mlx_get_data_addr(vars->fractal.img.mlx_img,
												   &vars->fractal.img.bpp, &vars->fractal.img.line_len,
												   &vars->fractal.img.endian);
		if (old_image)
			mlx_destroy_image(vars->fractal.mlx, old_image);
		mandelbort_set(vars);
		mlx_put_image_to_window(vars->fractal.mlx, vars->fractal.mlx_win,
								vars->fractal.img.mlx_img, 0, 0);
	}
	return (1);
}

int destroy_window(t_vars *vars)
{
	mlx_destroy_image(vars->fractal.mlx, vars->fractal.img.mlx_img);
	mlx_destroy_window(vars->fractal.mlx, vars->fractal.mlx_win);
}

int shift_view(int keycode, t_vars *vars)
{
	void *old_image;
	printf("key code %d \n", keycode);
	if (keycode == 65363)
	{
		vars->cords.MinRe += (vars->cords.MaxRe - vars->cords.MinRe) / 20;
		vars->cords.MaxRe += (vars->cords.MaxRe - vars->cords.MinRe) / 20;
	}
	else if (keycode == 65361)
	{
		vars->cords.MinRe -= (vars->cords.MaxRe - vars->cords.MinRe) / 20;
		vars->cords.MaxRe -= (vars->cords.MaxRe - vars->cords.MinRe) / 20;
	}
	else if (keycode == 65362)
	{
		vars->cords.MinIm += (vars->cords.MaxIm - vars->cords.MinIm) / 20;
		vars->cords.MaxIm += (vars->cords.MaxIm - vars->cords.MinIm) / 20;
	}
	else if (keycode == 65364)
	{
		vars->cords.MinIm -= (vars->cords.MaxIm - vars->cords.MinIm) / 20;
		vars->cords.MaxIm -= (vars->cords.MaxIm - vars->cords.MinIm) / 20;
	}
	else if (keycode == 65307)
	{
		destroy_window(vars);
		exit(0);
	}
	vars->cords.cx = (vars->cords.MaxRe + vars->cords.MinRe) / 2;
	vars->cords.cy = (vars->cords.MaxIm + vars->cords.MinIm) / 2;

	old_image = vars->fractal.img.mlx_img;
	vars->fractal.img.mlx_img = mlx_new_image(vars->fractal.mlx, vars->cords.ImageWidth, vars->cords.ImageHeight);
	vars->fractal.img.addr = mlx_get_data_addr(vars->fractal.img.mlx_img,
											   &vars->fractal.img.bpp, &vars->fractal.img.line_len,
											   &vars->fractal.img.endian);
	if (old_image)
		mlx_destroy_image(vars->fractal.mlx, old_image);
	mandelbort_set(vars);
	mlx_put_image_to_window(vars->fractal.mlx, vars->fractal.mlx_win,
							vars->fractal.img.mlx_img, 0, 0);
	return (1);
}
int close_it(int code, t_vars *mlx)
{
	printf("hna fin dir free\n");
}
int main(void)
{

	t_vars vars;

	vars.fractal.mlx = mlx_init();
	vars.fractal.mlx_win = mlx_new_window(vars.fractal.mlx, 600, 600, "Hello world!");
	cords_init(&vars.cords, 1);
	vars.fractal.img.mlx_img = mlx_new_image(vars.fractal.mlx, vars.cords.ImageWidth, vars.cords.ImageHeight);
	vars.fractal.img.addr = mlx_get_data_addr(vars.fractal.img.mlx_img, &vars.fractal.img.bpp, &vars.fractal.img.line_len, &vars.fractal.img.endian);
	mandelbort_set(&vars);
	vars.ini = 1;
	mlx_put_image_to_window(vars.fractal.mlx, vars.fractal.mlx_win, vars.fractal.img.mlx_img, 0, 0);
	mlx_mouse_hook(vars.fractal.mlx_win, &zoom_in, &vars);
	mlx_hook(vars.fractal.mlx_win, 17, 0, destroy_window, &vars);
	mlx_key_hook(vars.fractal.mlx_win, shift_view, &vars);
	mlx_loop(vars.fractal.mlx);
}
