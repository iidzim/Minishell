# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 15:30:22 by zqadiri           #+#    #+#              #
#    Updated: 2021/10/06 13:26:27 by iidzim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			=	minishell

SRCS 			=	./sources/minishell.c\
					./sources/parsing/get_next_token.c\
					./sources/parsing/lexer.c\
					./sources/parsing/lexer_utils.c\
					./sources/parsing/parser_utils.c\
					./sources/parsing/ast.c\
					./sources/parsing/utils.c\
					./sources/parsing/parser.c\
					./sources/parsing/realloc_ast.c\
					./sources/parsing/free.c
					
LIBFT_PATH 		= 	./libft

SRCS_EXEC		=	./sources/execution/builtins/cd/cd_builtin.c\
					./sources/execution/builtins/cd/helpers.c\
					./sources/execution/builtins/env_builtin.c\
					./sources/execution/builtins/exit_builtin.c\
					./sources/execution/builtins/pwd_builtin.c\
					./sources/execution/builtins/echo_builtin.c\
					./sources/execution/builtins/unset_builtin.c\
					./sources/execution/builtins/export/helpers.c\
					./sources/execution/builtins/export/export_builtin.c\
					./sources/execution/main_exec.c\
					./sources/execution/exec_helpers.c\
					./sources/execution/regular_cmd.c\
					./sources/execution/redirections.c\
					./sources/execution/n_pipes.c\
					./sources/execution/error_functions.c\
					./sources/execution/n_pipes_red.c\
					./sources/execution/signals.c\
					./sources/execution/here_doc.c\
					./sources/execution/here_doc_expander.c\
					./sources/execution/utils.c\
					./sources/execution/free_functions.c


OBJS			= 	${SRCS:.c=.o}
OBJS_EXEC		= 	${SRCS_EXEC:.c=.o}

INCLUDE 		= 	./includes
CC				= 	gcc
FLAGS           =  -Wall -Wextra -Werror -ltermcap -lreadline -g #-fsanitize=address
RM				= 	rm -f
LIBFLAGS 		= 	-I ./libft -L ./libft -L . ./libft/*.c 

all:			 ${NAME} libft_all

$(NAME):		$(SRCS) $(SRCS_EXEC) $(INCLUDE)
				@$(CC) -o  $(NAME) $(SRCS) -L /Users/$(USER)/goinfre/.brew/opt/readline/lib -I /Users/$(USER)/goinfre/.brew/opt/readline/include $(SRCS_EXEC) $(LIBFLAGS)  $(FLAGS) -g

clean:			libft_clean
				@${RM} ${OBJS} ${OBJS_EXEC}

fclean:			libft_fclean clean
				@${RM} ${NAME}

re:				fclean all

run:			re
				./$(NAME)

# make other makefiles compile with the -C flag
# The -C flag makes you go to the appropriate path and do the asked command

libft_all:
				@make -C $(LIBFT_PATH) all
				@cp ./libft/libft.a libft.a

libft_clean:
				@make -C $(LIBFT_PATH) clean

libft_fclean:
				@make -C $(LIBFT_PATH) fclean
				@$(RM) libft.a
				
.PHONY: 		all fclean clean re
