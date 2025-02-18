#ifndef FRACTOL_H
#define FRACTOL_H

# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>


typedef struct s_img
{
	void *mlx_img;
	char *addr;
	int bpp;
	int line_len;
	int endian;
} t_img;
typedef struct s_fractal
{
	void *mlx;
	void *mlx_win;
	t_img img;

} t_fractal;

typedef struct s_cords
{
	int ImageHeight;
	int ImageWidth;
	double MaxRe;
	double MinRe;
	double MinIm;
	double MaxIm;
	double Re_factor;
	double Im_factor;
	int MaxIterations;
	int color;
	double zoom;
	double cx;
	double cy;

} t_cords;

typedef struct s_compelxes
{
	int x;
	int y;
	int n;
	double z_re;
	double z_im;
	double c_re;
	double c_im;
	double z_re2;
	double z_im2;
	int isinside;
} t_compelxes;

typedef struct s_vars
{
	t_cords cords;
	t_fractal fractal;
	void (*draw)(struct s_vars *vars);
	int ini;
} t_vars;

void img_pix_put(t_img *img, int x, int y, int color);
int get_color(int iterations);
void mandelbort_helper(t_vars *vars, t_compelxes *compelxes);
void mandelbort_set(t_vars *vars);
void julia_set(t_vars *vars);
void cords_init(t_cords *cords, int zoomchecker);
void range_zoom_calculator(int keycode, double *range_re, double *range_im, t_vars *vars);
int zoom(int keycode, int x, int y, t_vars *vars);
int destroy_window(t_vars *vars);
int key_hook_helper(t_vars *vars, int keycode);
int key_hook(int keycode, t_vars *vars);
void perpendicular_set(t_vars *vars);

#endif