NAME = cub3D

SRC = main.c get_next_line.c get_next_line_utils.c libft/ft_putstr_fd.c libft/ft_strlen.c libft/ft_strtrim.c libft/ft_putchar_fd.c libft/ft_strchr.c libft/ft_substr.c libft/ft_strncmp.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS=  -Wall -Wextra -Werror -g3 -fsanitize=address

MLX = -lmlx -framework OpenGL -framework AppKit

$(RM) = rm -f 
  
all: $(NAME)

$(LIBFT): ./libft/*.c
	$(MAKE) -C ./libft

$(NAME): $(LIBFT) $(OBJ) 
	$(CC) $(CFLAGS) $(MLX) $(LIBFT) $(OBJ) -o $(NAME) 

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) fclean -C ./Libft
	$(RM) $(NAME)

re: fclean all