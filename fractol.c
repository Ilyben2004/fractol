/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <ibennaje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:07:00 by ibennaje          #+#    #+#             */
/*   Updated: 2025/02/08 20:33:47 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include <stdio.h>

typedef struct s_img
{
    void	*mlx_img;
    char	*addr;
    int		bpp; /* bits per pixel */
    int		line_len;
    int		endian;
}	t_img;
typedef struct s_fractal
{
	void *mlx;
	void *mlx_win;
	t_img img;
	
} t_fractal;

typedef struct s_cords
{
	int ImageHeight = 900;
	int ImageWidth = 900;
	double MaxRe = 0.47;
	double MinRe = -2.0 ;
	double MinIm = -1.2 ;
	double MaxIm = 1.12 ;
	double Re_factor = ((MaxRe - MinRe) / (ImageWidth - 1));
	double Im_factor = ((MaxIm - MinIm) / (ImageHeight - 1));
	int MaxIterations = 30;
	
} t_cords;


int	key_hook(int keycode,void *mlx_win)
{
	keycode++;
	mlx_win = NULL;
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;
    int		i;

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

int main(void)
{

	t_fractal fractal;
	int color;
	
	fractal.mlx = mlx_init();
	fractal.mlx_win = mlx_new_window(fractal.mlx, 900, 900, "Hello world!");

	int ImageHeight = 900;
	int ImageWidth = 900;
	double MaxRe = 0.47;
	double MinRe = -2.0 ;
	double MinIm = -1.2 ;
	double MaxIm = 1.12 ;
	double Re_factor = ((MaxRe - MinRe) / (ImageWidth - 1));
	double Im_factor = ((MaxIm - MinIm) / (ImageHeight - 1));
	int MaxIterations = 30;
	fractal.img.mlx_img = mlx_new_image(fractal.mlx,ImageWidth , ImageHeight);
	fractal.img.addr = mlx_get_data_addr(fractal.img.mlx_img,&fractal.img.bpp , &fractal.img.line_len, &fractal.img.endian);
	
	int x , y , n ;
	y = 0;
	
	while (y < ImageHeight)
	{
		double c_im = MaxIm - y * Im_factor;
		x = 0;
		while (x < ImageHeight)
		{
			double c_re = MinRe + x * Re_factor;

			double Z_re = c_re, Z_im = c_im;
			int isInside = 1;
			n = 0;
			while (n < MaxIterations)
			{
				double Z_re2 = Z_re * Z_re, Z_im2 = Z_im * Z_im;
				if (Z_re2 + Z_im2 > 4)
				{
					isInside = 0;
					break;
				}
				Z_im = 2 * Z_re * Z_im + c_im;
				Z_re = Z_re2 - Z_im2 + c_re;
				color = n;
				n++;
			}
			if (isInside)
			{
				img_pix_put(&(fractal.img), x, y,color * 1000);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal.mlx, fractal.mlx_win, fractal.img.mlx_img, 0, 0);
	mlx_loop(fractal.mlx);
}
