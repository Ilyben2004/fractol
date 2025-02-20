#include "fractol.h"

int ft_free(char * is_float ,char * intpart)
{
    if(is_float)
        free(intpart);
    return (1);
}
void error_exit()
{
    write(1, "********************** ibennaje fractol **********************\n", 64);
    write(1, "available fractals are : mandelbrot julia perpendicular\n", 57);
    write(1, " you only can do : ./fractol mandelbrot || ./ftactol perpendicular || ./fractol Julia \n", 88);
    write(1, "you have the option to give julia 2 parameters as number \n", 59);
    write(1, "./fractol xx.xxxxxxxxxx xx.xxxxxxxxxx \n", 40);
    write(1, "note that the decimal part only defined between 2 and -2 \n", 59);
    exit(1);
}

int ft_strcmp(char *s1, char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}
int is_number(char *num)
{
    char *is_float;
    char *intpart;
    int i;

    i = 0;
    if (!*num || num[ft_strlen(num) - 1] == '.')
        error_exit();
    if (num[i] == '+' || num[i] == '-')
        i++;
    is_float = ft_strchr(num, '.');
    while (num[i++])
        if (!ft_isdigit(num[i - 1]) && &num[i - 1] != is_float)
            error_exit();
    if (is_float)
        intpart = ft_substr(num, 0, is_float - num);
    else
        intpart = num;
    if (ft_strlen(intpart) > 2 || ft_atoi(intpart) > 2 || ft_atoi(intpart) < -2)
    {
        if (is_float)
            free(intpart);
        error_exit();
    }
    return (ft_free(is_float , intpart));
}

int number_len(long number)
{
    int i;

    i = 0;
    while (number != 0)
    {
        i++;
        number /= 10;
    }
    return (i);
}
void set_double_helper(char *float_part_s, double *d, long int_to_float, char *dbl)
{
    int free_s;
    int float_len;
    long float_part;
    int i;

    i = -1;
    free_s = 0;
    if (ft_strlen(float_part_s) > 10)
    {
        free_s = 1;
        float_part_s = ft_substr(float_part_s, 0, 10);
    }
    while (float_part_s[++i] == '0')
        int_to_float *= 10;;
    float_part = ft_atoi(float_part_s + i);
    printf("float part = %ld\n int_to_float = %ld \n" , float_part , int_to_float);
    float_len = number_len(float_part);
    while (float_len-- != 0)
        int_to_float *= 10;
    printf("float part = %ld\n int_to_float = %ld \n" , float_part , int_to_float);
    if (dbl[0] == '-')
        float_part = -float_part;
    *d += ((double)float_part / (double)int_to_float);
    if (free_s)
        free(float_part_s);
}

void set_double(double *d, char *dbl)
{
    char *float_part_s;
    long int_to_float;

    int_to_float = 1;
    *d = ft_atoi(dbl);
    float_part_s = ft_strchr(dbl, '.');
    if (float_part_s++)
        set_double_helper(float_part_s, d, int_to_float, dbl);
}
void julia_number_set(t_vars *vars, char *reel, char *img)
{
    set_double(&(vars->cords.julia_reel), reel);
    set_double(&(vars->cords.julia_img), img);
    printf("julia_rel = %f , julia_img = %f \n", vars->cords.julia_reel, vars->cords.julia_img);
    if (vars->cords.julia_reel > 2 || vars->cords.julia_reel < -2)
        error_exit();
    if (vars->cords.julia_img > 2 || vars->cords.julia_img < -2)
        error_exit();
}

void parse(int ac, char **av, t_vars *vars)
{
    if (ac == 1 || ac > 4)
        error_exit();
    else if (ac == 2 && ft_strcmp(av[1], "mandelbrot") == 0)
        vars->draw = mandelbort_set;
    else if (ft_strcmp(av[1], "julia") == 0)
    {
        vars->draw = julia_set;
        if (ac == 2)
        {
            vars->cords.julia_img = 0.35;
            vars->cords.julia_reel = 0.35;
        }
        else if (ac == 4 && is_number(av[2]) && is_number(av[3]))
            julia_number_set(vars, av[2], av[3]);
        else
            error_exit();
    }
    else if (ac == 2 && ft_strcmp(av[1], "perpendicular") == 0)
        vars->draw = perpendicular_set;
    else
        error_exit();
}
