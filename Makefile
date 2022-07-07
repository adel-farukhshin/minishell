
NAME = minishell

SRC =	main.c \
		utils.c \
		scanner.c \
		find_token.c \

OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))

CFLAGS = -Wall -Wextra -Werror 

SRCDIR = ./src/
OBJDIR = ./obj/
INCDIR = ./inc/

HEADERS = minishell.h scanner.h

${OBJDIR}%.o : ${SRCDIR}%.c ${addprefix ${INCDIR},${HEADERS}}
	cc ${CFLAGS} -c $< -I${INCDIR} -o $@

all : ${NAME}

${NAME} : obj ${OBJ} 
	${CC} ${CFLAGS} ${OBJ} -o $@ 

obj:
	mkdir -p $(OBJDIR)

clean :
	rm -f ${OBJ} $(addprefix $(OBJDIR), ${OBJ})
	
fclean : clean
	rm -f ${NAME}
		
re: fclean all

.PHONY: all clean fclean re
