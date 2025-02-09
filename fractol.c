/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <ibennaje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:07:00 by ibennaje          #+#    #+#             */
/*   Updated: 2025/02/09 22:14:16 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include <stdio.h>
#include <unistd.h>

typedef struct s_img
{
	void *mlx_img;
	char *addr;
	int bpp; /* bits per pixel */
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

void mandelbort_set(t_vars * vars)
{
	int x, y, n;
	y = 0;

	while (y < vars->cords.ImageHeight)
	{
		double c_im = vars->cords.MaxIm - y * vars->cords.Im_factor;
		x = 0;
		while (x < vars->cords.ImageHeight)
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
				img_pix_put(&(vars->fractal.img), x, y, vars->cords.color * 1000);
			}
			x++;
		}
		y++;
	}
}

void cords_init(t_cords *cords , int zoomchecker)
{
	if (zoomchecker == 1)
		cords->zoom = 1;
	if (zoomchecker == 4)
		cords->zoom -= 0.1;

	cords->ImageHeight = 900;
	cords->ImageWidth = 900;
	cords->MaxRe = 0.47 * cords->zoom;
	cords->MinRe = -2.0 * cords->zoom;
	cords->MinIm = -1.2 * cords->zoom;
	cords->MaxIm = 1.12 * cords->zoom;
	cords->Re_factor = ((cords->MaxRe - cords->MinRe) / (cords->ImageWidth - 1));
	cords->Im_factor = ((cords->MaxIm - cords->MinIm) / (cords->ImageHeight - 1));
	cords->MaxIterations = 30;
}

int mouse_hook(int keycode, t_vars * vars)
{
	mlx_destroy_image(vars->fractal.mlx,vars->fractal.img.mlx_img);
	vars->fractal.img.mlx_img = mlx_new_image(vars->fractal.mlx, vars->cords.ImageWidth, vars->cords.ImageHeight);
	vars->fractal.img.addr = mlx_get_data_addr(vars->fractal.img.mlx_img, &vars->fractal.img.bpp, &vars->fractal.img.line_len, &vars->fractal.img.endian);
	cords_init(&vars->cords , keycode);
	mandelbort_set(vars);
	mlx_put_image_to_window(vars->fractal.mlx, vars->fractal.mlx_win, vars->fractal.img.mlx_img, 0, 0);
	
	printf("keycode = %d\n", keycode);
	return (1);
}

int main(void)
{

	t_vars vars;

	vars.fractal.mlx = mlx_init();
	vars.fractal.mlx_win = mlx_new_window(vars.fractal.mlx, 900, 900, "Hello world!");
	cords_init(&vars.cords ,1);
	vars.fractal.img.mlx_img = mlx_new_image(vars.fractal.mlx, vars.cords.ImageWidth, vars.cords.ImageHeight);
	vars.fractal.img.addr = mlx_get_data_addr(vars.fractal.img.mlx_img, &vars.fractal.img.bpp, &vars.fractal.img.line_len, &vars.fractal.img.endian);
	mandelbort_set(&vars);
	vars.ini = 1;
	mlx_put_image_to_window(vars.fractal.mlx, vars.fractal.mlx_win, vars.fractal.img.mlx_img, 0, 0);
	printf("initialize \n");
	mlx_mouse_hook(vars.fractal.mlx_win, mouse_hook, &vars);
	sleep(1);
	mouse_hook(4,&vars);
	sleep(1);
	mouse_hook(4,&vars);
	mlx_loop(vars.fractal.mlx);
}
