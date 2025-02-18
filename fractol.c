/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <ibennaje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:07:00 by ibennaje          #+#    #+#             */
/*   Updated: 2025/02/18 12:54:27 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"



int main(int ac, char **av)
{
	t_vars vars;

	if (strcmp(av[1], "mandelbrot") == 0)
		vars.draw = mandelbort_set;
	if (strcmp(av[1], "julia") == 0)
		vars.draw = julia_set;
	//vars.draw = perpendicular_set;
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
