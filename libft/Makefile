# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 12:11:32 by zqadiri           #+#    #+#              #
#    Updated: 2021/10/04 10:37:10 by zqadiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libft.a
AR = ar
OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)
CFLAGS = -Wall -Wextra -Werror

SRC = ft_memalloc.c\
	  ft_is_white_space.c\
	  ft_memset.c\
	  ft_strequ.c\
	  ft_strcmp.c\
	  ft_bzero.c\
	  ft_memcpy.c\
	  ft_memccpy.c\
	  ft_memmove.c\
	  ft_memchr.c\
	  ft_memcmp.c\
	  ft_strlen.c\
	  ft_isalpha.c\
	  ft_isdigit.c\
	  ft_isalnum.c\
	  ft_isascii.c\
	  ft_isprint.c\
	  ft_toupper.c\
	  ft_tolower.c\
	  ft_strchr.c\
	  ft_strrchr.c\
	  ft_strncmp.c\
	  ft_strlcpy.c\
	  ft_strlcat.c\
	  ft_strnstr.c\
	  ft_atoi.c\
	  ft_calloc.c\
	  ft_strdup.c\
	  ft_substr.c\
	  ft_strjoin.c\
	  ft_split.c\
	  ft_itoa.c\
	  ft_strmapi.c\
	  ft_putchar_fd.c\
	  ft_putstr_fd.c\
	  ft_putendl_fd.c\
	  ft_putnbr_fd.c\
	  len.c\
	  ft_strchar.c\
	  ft_strlen_new.c\
	  ftstrcmp.c\
	  ft_joinchar.c\
	  ft_joinfree.c\
	  ft_strtrim.c
	  

all:	$(NAME)

$(NAME): 
		@$(CC) $(CFLAGS) -c $(SRC)
	 	@$(AR) rsc $(NAME) $(OBJ)
		@ranlib $(NAME)
clean:
		@rm -rf $(OBJ)

fclean: clean
		@rm -rf $(NAME)
re: fclean all
    
