CUB_SRCS_NAME	= 	main.c \
					parser.c \
					exec.c \
					utils.c

CUB_SRCS_DIR	= ./srcs

CUB_SRCS	= $(addprefix $(CUB_SRCS_DIR)/, $(CUB_SRCS_NAME))

CUB_OBJS	= $(CUB_SRCS_NAME:.c=.o)

NAME		= minishell

CUB_INCLUDES_DIR= ./includes

LIBFT_DIR	= ./libft

LIBFT_EXEC	= $(LIBFT_DIR)/libft.a

CC		= clang

RM		= rm -f

CFLAGS		= -Wall -Wextra -Werror

IFLAGS		= -I $(CUB_INCLUDES_DIR) -I $(LIBFT_DIR)

all:		$(LIBFT_EXEC) $(NAME)

$(NAME):	
		$(CC) -c $(IFLAGS) $(CUB_SRCS)
		$(CC) -o $@ $(CUB_OBJS) $(LIBFT_EXEC) $(CFLAGS)

$(LIBFT_EXEC):
		cd $(LIBFT_DIR) && $(MAKE)

clean:
		$(RM) $(CUB_OBJS)
		cd $(LIBFT_DIR) && $(MAKE) $@

fclean:		clean
		$(RM) $(NAME)
		cd $(LIBFT_DIR) && $(MAKE) $@

re:		fclean all

.PHONY:		all clean fclean re
