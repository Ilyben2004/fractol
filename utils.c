#include "fractol.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	get_color(int iterations)
{
	int	offset;

	if (iterations == 0)
		iterations = 1;
	offset = iterations * 100000;
	return (iterations * offset);
}

void	cords_init(t_cords *cords, int zoomchecker)
{
	if (zoomchecker == 1)
		cords->zoom = 1;
	if (zoomchecker == 4)
		cords->zoom -= 0.1;
	cords->image_height = HEIGHT;
	cords->image_width = WIDTH;
	cords->max_re = 2.0;
	cords->min_re = -2.0;
	cords->min_im = -2.0;
	cords->max_im = 2.0;
	cords->cx = 0;
	cords->cy = 0;
	cords->re_helper = (cords->max_re - cords->min_re) / (cords->image_width
			- 1);
	cords->im_helper = (cords->max_im - cords->min_im) / (cords->image_height
			- 1);
	cords->max_iterations = 100;
}

int	destroy_window(t_vars *vars)
{
	mlx_destroy_image(vars->fractal.mlx, vars->fractal.img.mlx_img);
	mlx_destroy_window(vars->fractal.mlx, vars->fractal.mlx_win);
	mlx_destroy_display(vars->fractal.mlx);
	free(vars->fractal.mlx);
}
