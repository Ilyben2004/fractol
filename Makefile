CC = cc

CFLAGS = -Wall -Wextra -Werror 

NAME = fractol

HEADER = fractol.h

MINILIBXDIR = minilibx-linux

SRCS = render.c utils.c fractols.c fractol.c libft.c parsing.c parsing2.c
OBJS = $(SRCS:.c=.o)

MLX = $(MINILIBXDIR)/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(OBJS)  -lmlx -lXext -lX11  $(MLX) -o $(NAME)

$(MLX):
	$(MAKE) -C $(MINILIBXDIR)


clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MINILIBXDIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all