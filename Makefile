SRCS		= 	srcs/main.c \
				srcs/parser.c \
				srcs/exec.c \
				srcs/exec_utils.c \
				srcs/utils.c \
				srcs/error.c \
				srcs/error_errno.c \
				srcs/realloc.c \
				srcs/quotes.c \
				srcs/construct.c \
				srcs/signal.c \
				srcs/exit.c \
				srcs/ft_check_atoi.c \
				srcs/redirections.c \
				srcs/arg.c \
				srcs/builtins1.c \
				srcs/builtins2.c \
				srcs/builtins_utils1.c \
				srcs/builtins_utils2.c \
				srcs/builtins_utils3.c \
				srcs/cmd.c \
				srcs/cmd_utils.c \
				srcs/files.c

OBJS		= $(SRCS:.c=.o)

NAME		= minishell

LIBFT_EXEC	= $(LIBFT_DIR)/libft.a

CC			= clang

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -I ./includes

all:		$(NAME)

$(NAME):	$(OBJS)
		make bonus -C ./libft
		$(CC) -o ${NAME} ${OBJS} ./libft/*.o ${CFLAGS}

clean:
		$(MAKE) clean -C ./libft
		$(RM) $(OBJS)

fclean:		clean
		$(MAKE) fclean -C ./libft
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re