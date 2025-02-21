/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <ibennaje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:56:26 by ibennaje          #+#    #+#             */
/*   Updated: 2025/02/21 13:16:08 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*((int *) pixel) = color;
}

int	get_color(int iterations, t_vars *vars)
{
	int	r;
	int	g;
	int	b;

	if (!iterations)
		iterations = 1;
	r = (iterations * 10) + vars->cords.color_shift;
	g = (iterations * 20) + vars->cords.color_shift;
	b = (iterations * 30) + vars->cords.color_shift;
	return (((r << 16) | (g << 8) | b));
}

void	cords_init(t_cords *cords)
{
	cords->image_height = HEIGHT;
	cords->image_width = WIDTH;
	cords->max_re = 2;
	cords->min_re = -2;
	cords->min_im = -2;
	cords->max_im = 2;
	cords->cx = 0;
	cords->cy = 0;
	cords->re_helper = (cords->max_re - cords->min_re) / (cords->image_width
			- 1);
	cords->im_helper = (cords->max_im - cords->min_im) / (cords->image_height
			- 1);
	cords->max_iterations = 50;
	cords->color_shift = 0;
}

int	destroy_window(t_vars *vars)
{
	mlx_destroy_image(vars->fractal.mlx, vars->fractal.img.mlx_img);
	mlx_destroy_window(vars->fractal.mlx, vars->fractal.mlx_win);
	mlx_destroy_display(vars->fractal.mlx);
	free(vars->fractal.mlx);
	exit(0);
}

int	destroy_window_helper(int code, t_vars *vars)
{
	code++;
	return (destroy_window(vars));
}
