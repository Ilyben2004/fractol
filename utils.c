#include "fractol.h"

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



int destroy_window(t_vars *vars)
{
	mlx_destroy_image(vars->fractal.mlx, vars->fractal.img.mlx_img);
	mlx_destroy_window(vars->fractal.mlx, vars->fractal.mlx_win);
	mlx_destroy_display(vars->fractal.mlx);
	free(vars->fractal.mlx);
}


