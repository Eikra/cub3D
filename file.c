NAME = cub3D

SRC = main.c get_next_line.c get_next_line_utils.c libft/ft_putstr_fd.c libft/ft_strlen.c libft/ft_strtrim.c libft/ft_putchar_fd.c libft/ft_strchr.c libft/ft_substr.c libft/ft_strncmp.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS=  -Wall -Wextra -Werror #-g3 -fsanitize=address

MLX = -lmlx -framework OpenGL -framework AppKit

$(RM) = rm -f 
  
all:
	@$(MAKE) -C minilibx
	@$(MAKE) -j $(NAME)

$(LIBFT): ./libft/*.c
	$(MAKE) -C ./libft

$(NAME): $(OBJ) 
	${CC} $(CFLAGS) -o $(NAME) $(OBJ) -L minilibx -l mlx
	@install_name_tool -change libmlx.a @loader_path/minilibx/libmlx.a $(NAME)

clean:
	@$(MAKE) clean -C minilibx
	$(RM) $(OBJ)

fclean: clean
	@$(MAKE) clean -C minilibx
	$(RM) $(NAME)

re: fclean all