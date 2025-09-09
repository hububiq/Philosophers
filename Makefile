CC = cc 
NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread
CSRC = main.c init.c routines.c routine_functions.c clean.c utils.c
COBJ = ${CSRC:.c=.o}


all : ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${COBJ}
	${CC} ${CFLAGS} -o $@ ${COBJ}

clean: 
	rm -f ${COBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all




