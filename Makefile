SRCS_NAME	= 	main.c \
					parser.c \
					exec.c \
					utils.c \
					quotes.c \
					construct.c \
					signal.c \
					exit.c \
					redirections.c \
					arg.c \
					builtins.c \
					builtins_utils.c \
					cmd.c \
					files.c

SRCS_DIR	= ./srcs

SRCS		= $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))

OBJS		= $(SRCS_NAME:.c=.o)

NAME		= minishell

INCLUDES_DIR= ./includes

LIBFT_DIR	= ./libft

LIBFT_EXEC	= $(LIBFT_DIR)/libft.a

CC			= clang

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

IFLAGS		= -I $(INCLUDES_DIR) -I $(LIBFT_DIR)

all:		$(LIBFT_EXEC) $(NAME)

deb:		$(NAME)

$(NAME):	
		$(CC) -c $(IFLAGS) $(SRCS)
		$(CC) -o $@ $(OBJS) $(LIBFT_EXEC) $(CFLAGS)

$(LIBFT_EXEC):
		cd $(LIBFT_DIR) && $(MAKE)

clean:
		$(RM) $(OBJS)
		cd $(LIBFT_DIR) && $(MAKE) $@

fclean:		clean
		$(RM) $(NAME)
		cd $(LIBFT_DIR) && $(MAKE) $@

clean_deb:	
		$(RM) $(OBJS)
		$(RM) $(NAME)

re:		fclean all

debug:	clean_deb deb

.PHONY:		all clean fclean re debug
