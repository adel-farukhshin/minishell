NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
		ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c\
		 ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strchr.c \
		 ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c\
		  ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c ft_strmapi.c ft_striteri.c ft_strtrim.c\
		  ft_itoa.c ft_split.c 

SRC_B = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c\
			ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c\
				ft_lstmap_bonus.c

INCLUDES = libft.h

OBJ = $(patsubst %.c, %.o, $(SRC))
OBJ_B = $(patsubst %.c, %.o, $(SRC_B))

D_FILES = $(patsubst %.c, %.d, $(SRC))
D_FILES_B = $(patsubst %.c, %.d, $(SRC_B))

FLAGS = -Wall -Werror -Wextra

all: ${NAME}

${NAME}: ${OBJ}
		ar rcs ${NAME} $?

%.o : %.c
		gcc ${FLAGS} -c $< -o $@ -MD

include ${wildcard $(D_FILES) $(D_FILES_B)}

bonus:
		@make OBJ="$(OBJ_B)" all
clean:
		@rm -f $(OBJ) $(OBJ_B) $(D_FILES) $(D_FILES_B)

fclean: clean
		@rm -f ${NAME}

re: fclean all 

.PHONY: all clean fclean re bonus
