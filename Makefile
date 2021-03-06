
.PHONY: all clean fclean re debug dvs

NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = 	main.c utils.c gettime.c philosopher.c ft_free.c \
		parsing.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

debug: CFLAGS += -fsanitize=address -g
debug: fclean all;

dvs: CFLAGS += -g
dvs: fclean all;


$(NAME) :${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
		rm -f ${OBJS}

fclean:	clean
		rm -f ${NAME}

re: fclean all
