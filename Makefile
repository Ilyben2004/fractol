PRG = fractol 
#MLXFILESO = $(MLXFILES:.c=.o)
CFLAGS = -lmlx -lXext -lX11 -lm
FRACTOL = fractol.c
SRCS = fractols.c render.c utils.c 
OSRCS = $(SRCS:.c=.o)
all : $(PRG)


$(PRG) : $(FRACTOL) $(OSRCS)
	cc $(FRACTOL)  $(CFLAGS)    $(OSRCS) -o $(PRG)

clean :
	rm -rf $(OSRCS)