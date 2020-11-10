SRCS		= ft_isalnum.c ft_isdigit.c ft_strlen.c ft_tolower.c ft_isalpha.c ft_strchr.c ft_strlcpy.c ft_strncmp.c ft_strcmp.c ft_strrchr.c ft_toupper.c ft_strlcat.c ft_atoi.c ft_isascii.c ft_memset.c ft_isprint.c ft_strnstr.c ft_bzero.c ft_memcpy.c ft_memcmp.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c ft_split.c ft_itoa.c ft_putchar_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_strmapi.c ft_strtrim.c ft_memmove.c ft_putchar.c ft_putstr.c ft_putnbr.c get_next_line.c get_next_line_utils.c

SRCS_BONUS	= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS		= ${SRCS:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

FICHIER_H	= libft.h

NAME		= libft.a

CC			= clang

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -D BUFFER_SIZE=1024 -I .${FICHIER_H}

all:		${NAME}

${NAME}:	${OBJS} ${OBJS_BONUS}
			ar rc ${NAME} ${OBJS} ${OBJS_BONUS}
			ranlib ${NAME}

bonus:		${OBJS} ${OBJS_BONUS}
			ar rc ${NAME} ${OBJS} ${OBJS_BONUS}
			ranlib ${NAME}

clean:
			${RM} ${OBJS} ${OBJS_BONUS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
