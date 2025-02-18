#include "fractol.h"

int key_hook_helper(t_vars *vars, int keycode)
{
	if (keycode == 65363)
	{
		vars->cords.MinRe += (vars->cords.MaxRe - vars->cords.MinRe) / 20;
		vars->cords.MaxRe += (vars->cords.MaxRe - vars->cords.MinRe) / 20;
		return (1);
	}
	else if (keycode == 65361)
	{
		vars->cords.MinRe -= (vars->cords.MaxRe - vars->cords.MinRe) / 20;
		vars->cords.MaxRe -= (vars->cords.MaxRe - vars->cords.MinRe) / 20;
		return (1);
	}
	else if (keycode == 65362)
	{
		vars->cords.MinIm += (vars->cords.MaxIm - vars->cords.MinIm) / 20;
		vars->cords.MaxIm += (vars->cords.MaxIm - vars->cords.MinIm) / 20;
		return (1);
	}
	else if (keycode == 65364)
	{
		vars->cords.MinIm -= (vars->cords.MaxIm - vars->cords.MinIm) / 20;
		vars->cords.MaxIm -= (vars->cords.MaxIm - vars->cords.MinIm) / 20;
		return (1);
	}
	return (0);
}

int key_hook(int keycode, t_vars *vars)
{
	void *old_image;

	if (key_hook_helper(vars, keycode))
	{
		vars->cords.cx = (vars->cords.MaxRe + vars->cords.MinRe) / 2;
		vars->cords.cy = (vars->cords.MaxIm + vars->cords.MinIm) / 2;

		old_image = vars->fractal.img.mlx_img;
		vars->fractal.img.mlx_img = mlx_new_image(vars->fractal.mlx, vars->cords.ImageWidth, vars->cords.ImageHeight);
		vars->fractal.img.addr = mlx_get_data_addr(vars->fractal.img.mlx_img,
												   &vars->fractal.img.bpp, &vars->fractal.img.line_len,
												   &vars->fractal.img.endian);
		if (old_image)
			mlx_destroy_image(vars->fractal.mlx, old_image);
		vars->draw(vars);
		mlx_put_image_to_window(vars->fractal.mlx, vars->fractal.mlx_win,
								vars->fractal.img.mlx_img, 0, 0);
	}
	else if (keycode == 65307)
	{
		destroy_window(vars);
		exit(0);
	}
	return (1);
}

void range_zoom_calculator(int keycode, double *range_re, double *range_im, t_vars *vars)
{
	double zoom = 1.1;
	if (keycode == 4)
	{
		*range_re = (vars->cords.MaxRe - vars->cords.MinRe) / zoom;
		*range_im = (vars->cords.MaxIm - vars->cords.MinIm) / zoom;
	}
	else
	{
		*range_re = (vars->cords.MaxRe - vars->cords.MinRe) * zoom;
		*range_im = (vars->cords.MaxIm - vars->cords.MinIm) * zoom;
	}
	vars->cords.MinRe = vars->cords.cx - ((*range_re) / 2);
	vars->cords.MaxRe = vars->cords.cx + ((*range_re) / 2);
	vars->cords.MinIm = vars->cords.cy - ((*range_im) / 2);
	vars->cords.MaxIm = vars->cords.cy + ((*range_im) / 2);
	vars->cords.Re_factor = ((vars->cords.MaxRe - vars->cords.MinRe) / (vars->cords.ImageWidth - 1));
	vars->cords.Im_factor = ((vars->cords.MaxIm - vars->cords.MinIm) / (vars->cords.ImageHeight - 1));
}

int zoom(int keycode, int x, int y, t_vars *vars)
{
	double range_re;
	double range_im;
	void *old_image;
	static int zoom;

	if (keycode == 4 || keycode == 5)
	{
		range_zoom_calculator(keycode, &range_re, &range_im, vars);
		old_image = vars->fractal.img.mlx_img;
		vars->fractal.img.mlx_img = mlx_new_image(vars->fractal.mlx, vars->cords.ImageWidth, vars->cords.ImageHeight);
		vars->fractal.img.addr = mlx_get_data_addr(vars->fractal.img.mlx_img,
												   &vars->fractal.img.bpp, &vars->fractal.img.line_len,
												   &vars->fractal.img.endian);
		if (old_image)
			mlx_destroy_image(vars->fractal.mlx, old_image);
		vars->draw(vars);
		mlx_put_image_to_window(vars->fractal.mlx, vars->fractal.mlx_win,
								vars->fractal.img.mlx_img, 0, 0);
		zoom++;
	}
}