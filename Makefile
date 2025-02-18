CC = cc

CFLAGS = 

NAME = fractol

HEADER = fractol.h

MINILIBXDIR = minilibx-linux

SRCS = render.c utils.c fractols.c fractol.c
OBJS = $(SRCS:.c=.o)

MLX = $(MINILIBXDIR)/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -L$(MINILIBXDIR) -lmlx -lXext -lX11 -lm -o $(NAME)

$(MLX):
	$(MAKE) -C $(MINILIBXDIR)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MINILIBXDIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all