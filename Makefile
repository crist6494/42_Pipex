NAME = pipex

CC	= gcc

CFLAGS	=	-Wall -Wextra -Werror

SRC_DIR	=	./src/

OBJ_DIR	=	./obj/

SRCS =	pipex.c \
		utils.c \

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: lib obj $(NAME) 

obj:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I ./includes/ -I ./42-library/ -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L ./42-library -l ft -o $(NAME)

lib:
	make -C	./42-library

clean:
	make clean -C ./42-library
	rm -rf obj $(OBJS) $(CHECKER_OBJS)

fclean: clean
	make fclean -C ./42-library
	rm -rf obj $(NAME) $(CHECKER_NAME)

re: fclean all

.PHONY:     all clean fclean re