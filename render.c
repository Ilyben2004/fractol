#include "fractol.h"


int shift_color_helper(t_vars * vars , int keycode)
{
	if (keycode == 99)
	{
		vars->cords.color_shift += 5;
		return (3);
	}
	if (keycode == 118)
	{
		vars->cords.color_shift -= 5;
		return (1);
	}
	return (0);
}
static	int key_hook_helper(t_vars *vars, int keycode)
{
	if (keycode == 65363) //right
	{
		vars->cords.min_re += (vars->cords.max_re - vars->cords.min_re) / 10;
		vars->cords.max_re += (vars->cords.max_re - vars->cords.min_re) / 10;
		return (1);
	}
	else if (keycode == 65361)//left 
	{
		vars->cords.min_re -= (vars->cords.max_re - vars->cords.min_re) / 10;
		vars->cords.max_re -= (vars->cords.max_re - vars->cords.min_re) / 10;
		return (1);
	}
	else if (keycode == 65362) // up
	{
		vars->cords.min_im += (vars->cords.max_im - vars->cords.min_im) / 10;
		vars->cords.max_im += (vars->cords.max_im - vars->cords.min_im) / 10;
		return (1);
	}
	else if (keycode == 65364)//down
	{
		vars->cords.min_im -= (vars->cords.max_im - vars->cords.min_im) / 10;
		vars->cords.max_im -= (vars->cords.max_im - vars->cords.min_im) / 10;
		return (1);
	}
	return (shift_color_helper(vars , keycode));
}

int	key_hook(int keycode, t_vars *vars)
{
	void	*old_image;

	if (key_hook_helper(vars, keycode))
	{
		vars->cords.cx = (vars->cords.max_re + vars->cords.min_re) / 2;
		vars->cords.cy = (vars->cords.max_im + vars->cords.min_im) / 2;
		old_image = vars->fractal.img.mlx_img;
		vars->fractal.img.mlx_img = mlx_new_image(vars->fractal.mlx,
				vars->cords.image_width, vars->cords.image_height);
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

static	void	range_zoom_calculator(int keycode, double *range_re, double *range_im,
		t_vars *vars)
{
	double	zoom;

	zoom = 1.11;
	if (keycode == 4)
	{
		*range_re = fabs(vars->cords.max_re - vars->cords.min_re) / zoom;
		*range_im = fabs(vars->cords.max_im - vars->cords.min_im)/ zoom;
	}
	else
	{
		*range_re = fabs(vars->cords.max_re - vars->cords.min_re) * zoom;
		*range_im = fabs(vars->cords.max_im - vars->cords.min_im)* zoom;
	}
	vars->cords.min_re = vars->cords.cx - ((*range_re) / 2);
	vars->cords.max_re = vars->cords.cx + ((*range_re) / 2);
	vars->cords.min_im = vars->cords.cy - ((*range_im) / 2);
	vars->cords.max_im = vars->cords.cy + ((*range_im) / 2);
	vars->cords.re_helper = (fabs(vars->cords.max_re - vars->cords.min_re)
			/ (vars->cords.image_width - 1));
	vars->cords.im_helper = (fabs(vars->cords.max_im - vars->cords.min_im)
			/ (vars->cords.image_height - 1));
}

int	zoom(int keycode, int x, int y, t_vars *vars)
{
	double	range_re;
	double	range_im;
	void	*old_image;

	(void)x;
	(void)y;
	if (keycode == 4 || keycode == 5)
	{
		range_zoom_calculator(keycode, &range_re, &range_im, vars);
		old_image = vars->fractal.img.mlx_img;
		vars->fractal.img.mlx_img = mlx_new_image(vars->fractal.mlx,
				vars->cords.image_width, vars->cords.image_height);
		vars->fractal.img.addr = mlx_get_data_addr(vars->fractal.img.mlx_img,
				&vars->fractal.img.bpp, &vars->fractal.img.line_len,
				&vars->fractal.img.endian);
		if (old_image)
			mlx_destroy_image(vars->fractal.mlx, old_image);
		vars->draw(vars);
		mlx_put_image_to_window(vars->fractal.mlx, vars->fractal.mlx_win,
			vars->fractal.img.mlx_img, 0, 0);
	}
	return(1);
}
