/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <ibennaje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:07:00 by ibennaje          #+#    #+#             */
/*   Updated: 2025/02/05 17:24:13 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	double x , y;
	x = y = 0;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 900, 900, "Hello world!");
	while (x < 900)
	{
		while (y < 900)
		{
				double c_real = -2;
				double c_img = 1;
				double z_real = 0;
				double z_img = 0;
				double count = 0;
				double max_count = 1000;
				while ((z_real * z_real) + (z_img * z_img) <= 2 * 2 && (count < max_count))
				{
					double next_zreal = (z_real * z_real) + c_real;
					double next_zimg = (z_img * z_img) + c_img;
					z_real = next_zreal;
					z_img = next_zimg;
					count++;
				}
				if (count == max_count)
				{
					mlx_pixel_put(mlx, mlx_win, x, y, 0x000000);
					printf("here\n");		
				}
				else 
				{
					mlx_pixel_put(mlx, mlx_win, x, y, 0xFF0000);
					printf("no here\n");
				}	
				y++;
				
		}
		x++;
	}
	
	//mlx_pixel_put(mlx, mlx_win, 450, 450, 0xFFFFFF);
	mlx_loop(mlx);
}
