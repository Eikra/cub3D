NAME = cub3D

SRC = main.c parcing/parcing1.c parcing/parcing2.c parcing/parcing3.c parcing/parcing4.c parcing/parcing5.c parcing/parcing6.c parcing/parcing7.c get_next_line.c get_next_line_utils.c libft/ft_putstr_fd.c libft/ft_isdigit.c libft/ft_strlen.c libft/ft_strtrim.c libft/ft_putchar_fd.c libft/ft_strchr.c libft/ft_substr.c libft/ft_strncmp.c libft/ft_split.c\
	rendring/data.c rendring/draw_rays.c rendring/draw_view.c rendring/minimap.c rendring/player_move.c rendring/raycasting.c

CC = cc

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

OBJ = $(SRC:.c=.o)



CFLAGS=  -Wall -Wextra -Werror -g3 -fsanitize=address

MLX_DIR = mlx

MLX = libmlx.dylib

$(RM) = rm -f 
  
all: $(NAME)
 
$(NAME): $(OBJ)
		${CC} $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) -l mlx
		@install_name_tool -change $(MLX) @loader_path/$(MLX_DIR)/$(MLX) $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all