NAME 		= hangman

FILENAMES	= hangman.c http_request.c utilities.c

SRCS		= $(addprefix src/, $(FILENAMES))

INC			= -I includes/ -I/usr/local/include

LIB			= -L./libraries -lft -L/usr/local/lib -lcurl -lldap -lz 

OBJS 		= $(SRCS:.c=.o)

CC 			= gcc

all: $(NAME); @echo successfully created executable \‘hangman\’

$(NAME):
	@$(CC) -o $(NAME) $(SRCS) $(INC) $(LIB) $(FRAMEWORK)

clean:
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
