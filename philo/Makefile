CC = cc 
NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread
OBJ_DIR = obj
RM = rm -f
CSRC = main.c init.c routines.c routine_functions.c clean.c utils.c
#prefix to add obj/.c
COBJ = $(addprefix ${OBJ_DIR}/, ${CSRC:.c=.o})

all : ${NAME}

#{OBJ_DIR}/  - important to convert stuff there
#flag -p creats the directory if it doesnt exist.
# @mkdir for silent command
${OBJ_DIR}/%.o: %.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${COBJ}
	${CC} ${CFLAGS} ${COBJ} -o $@

#recursively, to delete the directory contents first
clean: 
	${RM} -r ${OBJ_DIR}

fclean: clean
	${RM} ${NAME}

re: fclean all




