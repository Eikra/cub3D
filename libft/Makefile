# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 19:REC:41 by iecharak          #+#    #+#              #
#    Updated: 2022/11/03 04:REC:41 by iecharak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
SRC = ft_atoi.c       ft_isalpha.c    ft_memchr.c     ft_memset.c     ft_putstr_fd.c  ft_strlcat.c    ft_strnstr.c    ft_tolower.c \
		ft_bzero.c      ft_isascii.c    ft_memcmp.c     ft_putchar_fd.c ft_strchr.c     ft_strlcpy.c    ft_strrchr.c    ft_toupper.c\
		ft_calloc.c     ft_isdigit.c    ft_memcpy.c     ft_putendl_fd.c ft_strdup.c     ft_strlen.c     ft_strtrim.c ft_itoa.c\
		ft_isalnum.c    ft_isprint.c    ft_memmove.c    ft_putnbr_fd.c  ft_strjoin.c    ft_strncmp.c    ft_substr.c ft_split.c	ft_strmapi.c	ft_striteri.c\

BONUS = ft_lstnew_bonus.c	ft_lstadd_front_bonus.c ft_lstmap_bonus.c	ft_lstsize_bonus.c	ft_lstlast_bonus.c	ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c\

OBJ = $(SRC:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)

all : ${NAME}

${NAME} : ${OBJ} 
	ar rc ${NAME} ${OBJ}

bonus : $(BONUS_OBJS)  ${OBJ}
	ar rc ${NAME} $(BONUS_OBJS) ${OBJ}

clean :
	${RM} ${OBJ} $(BONUS_OBJS)

fclean : clean
	${RM} ${NAME} ${OBJ} $(BONUS_OBJS)

re : fclean all

.PHONY : clean fclean 
