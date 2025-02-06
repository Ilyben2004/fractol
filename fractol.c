/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <ibennaje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:07:00 by ibennaje          #+#    #+#             */
/*   Updated: 2025/02/06 04:48:20 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

int main(void)
{
	void *mlx;
	void *mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 900, 900, "Hello world!");
	double MinRe = -2.0;
	int ImageHeight = 900;
	int ImageWidth = 900;
	double MaxRe = 0.47;
	double MinIm = -1.2;
	double MaxIm = 1.12;
	double Re_factor = (MaxRe - MinRe) / (ImageWidth - 1);
	double Im_factor = (MaxIm - MinIm) / (ImageHeight - 1);
	unsigned int MaxIterations = 100;

	for (int y = 0; y < ImageHeight; ++y)
	{
		double c_im = MaxIm - y * Im_factor;
		for (int x = 0; x < ImageWidth; ++x)
		{
			double c_re = MinRe + x * Re_factor;

			double Z_re = c_re, Z_im = c_im;
			int isInside = 1;
			for (unsigned int n = 0; n < MaxIterations; ++n)
			{
				double Z_re2 = Z_re * Z_re, Z_im2 = Z_im * Z_im;
				if (Z_re2 + Z_im2 > 4)
				{
					isInside = 0;
					break;
				}
				Z_im = 2 * Z_re * Z_im + c_im;
				Z_re = Z_re2 - Z_im2 + c_re;
			}
			if (isInside)
				mlx_pixel_put(mlx, mlx_win, x, y, 0xFFFFFF);
		}
	}
	mlx_loop(mlx);
}
