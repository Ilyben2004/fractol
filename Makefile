PRG = fractol 
#MLXFILESO = $(MLXFILES:.c=.o)
CFLAGS =
FRACTOL = fractol.c
all : $(PRG)


$(PRG) : $(FRACTOL)
	cc $(FRACTOL) $(CFLAGS) -lmlx -lXext -lX11 -lm   -o $(PRG) 