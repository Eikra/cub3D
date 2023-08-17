NAME = cub3D

SRC = main.c get_next_line.c get_next_line_utils.c libft/ft_putstr_fd.c libft/ft_strlen.c libft/ft_strtrim.c libft/ft_putchar_fd.c libft/ft_strchr.c libft/ft_substr.c libft/ft_strncmp.c libft/ft_split.c

OBJ = $(SRC:.c=.o)

CC = clang

CFLAGS=  -Wall -Wextra -Werror -g3 -fsanitize=address

MLX = -lmlx -framework OpenGL -framework AppKit

$(RM) = rm -f 
  
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) 
	$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $(NAME) 

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all