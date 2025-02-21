CC = cc

CFLAGS = -Wall -Wextra -Werror 

NAME = fractol


SRCS = render.c utils.c fractols.c fractol.c libft.c parsing.c parsing2.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -lmlx -lXext -lX11 -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
