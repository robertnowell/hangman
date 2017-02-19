NAME 		= wireframe

FILENAMES	= main.c create.c draw.c rotate.c rows_columns_vectors.c

SRCS		= $(addprefix src/, $(FILENAMES))

INC			+= -I includes/

LIB			= -L./libraries -lft -lmlx

FRAMEWORK 	= -framework OpenGL -framework Appkit

OBJS 		= $(SRCS:.c=.o)

CC 			= gcc

all: $(NAME); @echo "successfully created executable 'wireframe'"

$(NAME):
	@$(CC) -o $(NAME) $(SRCS) $(INC) $(LIB) $(FRAMEWORK)

clean:
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
