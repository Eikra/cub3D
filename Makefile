NAME = cub3D

SRC = main.c parcing/parcing1.c parcing/parcing2.c parcing/parcing3.c parcing/parcing4.c parcing/parcing5.c parcing/parcing6.c parcing/parcing7.c get_next_line.c get_next_line_utils.c libft/ft_putstr_fd.c libft/ft_isdigit.c libft/ft_strlen.c libft/ft_strtrim.c libft/ft_putchar_fd.c libft/ft_strchr.c libft/ft_substr.c libft/ft_strncmp.c libft/ft_split.c

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

OBJ = $(SRC:.c=.o)

CC = clang

CFLAGS=  -Wall -Wextra -Werror -g3 -fsanitize=address

MLX = -lmlx -framework OpenGL -framework AppKit

$(RM) = rm -f 
  
all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) 

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all