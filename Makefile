SRCS	=	main.c \
			./sources/utils/lib.c \
			./sources/utils/print_utils.c \
			./sources/utils/remove_all_quote.c \
			./sources/utils/remove_all.c \
			./sources/utils/utils.c \
			./sources/utils/utils01.c \
			./sources/utils/utils02.c \
			./sources/utils/utils03.c \
			./sources/utils/print_utils.c \
			./sources/errors/put_error.c \
			./sources/errors/errors.c \
			./sources/lexer/init_lexer.c \
			./sources/lexer/init.c \
			./sources/free/free_lexer.c \
			./sources/free/free_env.c \
			./sources/redirection/redirection.c \
			./sources/exec/exec.c \
			./sources/built_in/build_in.c \
			./sources/built_in/cd.c \
			./sources/built_in/echo.c \
			./sources/built_in/env.c \
			./sources/built_in/check_export.c \
			./sources/built_in/export.c \
			./sources/built_in/pwd.c \
			./sources/built_in/unset.c \
			./sources/built_in/shlvl.c \
			./sources/built_in/utils_built_in1.c \
			./sources/built_in/utils_built_in2.c \
			./sources/built_in/exit.c

OBJS	=	${SRCS:.c=.o}

CC		=	cc -Wall -Werror -Wextra -g3 -fsanitize=address
RM		=	rm -f
NAME	=	minishell

all:		${NAME}

.c.o:
			$(CC) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) -lreadline 

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

git:
			git add *
			git commit -m "COMMIT"
			git push chelou master

.PHONY:		all clean fclean re