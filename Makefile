NAME = philo
SRCS = ${shell find "." -name "*.c"}
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

all: ${NAME}

${NAME}:
	@${CC} ${CFLAGS} -L. -lft ${SRCS} -o ${NAME}

clean:
	@${RM} ${NAME}

re: clean all

.PHONY: clean fclean re all