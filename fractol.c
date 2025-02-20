/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <ibennaje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:07:00 by ibennaje          #+#    #+#             */
/*   Updated: 2025/02/20 22:37:14 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_vars	vars;

	parse(ac , av , &vars);
	vars.fractal.mlx = mlx_init();
	if (!vars.fractal.mlx)
		return (0);
	vars.fractal.mlx_win = mlx_new_window(vars.fractal.mlx, WIDTH, HEIGHT,
			"fractol");
	if (!vars.fractal.mlx_win)
		return (free(vars.fractal.mlx), 0);
	cords_init(&vars.cords);
	vars.fractal.img.mlx_img = mlx_new_image(vars.fractal.mlx,
			vars.cords.image_width, vars.cords.image_height);
	vars.fractal.img.addr = mlx_get_data_addr(vars.fractal.img.mlx_img,
			&vars.fractal.img.bpp, &vars.fractal.img.line_len,
			&vars.fractal.img.endian);
	vars.draw(&vars);
	mlx_put_image_to_window(vars.fractal.mlx, vars.fractal.mlx_win,
		vars.fractal.img.mlx_img, 0, 0);
	mlx_mouse_hook(vars.fractal.mlx_win, &zoom, &vars);
	mlx_hook(vars.fractal.mlx_win, 17, 0, destroy_window, &vars);
	mlx_key_hook(vars.fractal.mlx_win, key_hook, &vars);
	mlx_loop(vars.fractal.mlx);
}
