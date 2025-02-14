#ifndef FRACTOL_H
# define FRACTOL_H

#include <mlx.h>
#include <stdio.h>
#include <unistd.h>

# define MIN_ZOOM 0.000001
# define MAX_ZOOM 2.0
# define ZOOM_FACTOR 0.1

typedef struct s_img
{
    void    *mlx_img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_img;

typedef struct s_fractal
{
    void    *mlx;
    void    *mlx_win;
    t_img   img;
}   t_fractal;

typedef struct s_cords
{
    int     ImageHeight;
    int     ImageWidth;
    double  MaxRe;
    double  MinRe;
    double  MinIm;
    double  MaxIm;
    double  Re_factor;
    double  Im_factor;
    int     MaxIterations;
    int     color;
    double  zoom;
    double  center_x;
    double  center_y;
}   t_cords;

typedef struct s_vars
{
    t_cords     cords;
    t_fractal   fractal;
    int         ini;
}   t_vars;

void    img_pix_put(t_img *img, int x, int y, int color);
void    mandelbort_set(t_vars *vars);
void    cords_init(t_cords *cords, int zoomchecker, int mouse_x, int mouse_y);
int     mouse_hook(int keycode, int x, int y, t_vars *vars);

#endif