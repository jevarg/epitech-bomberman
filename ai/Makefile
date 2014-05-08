SRC = 	main.cpp \
	test.cpp \
	cppLua.cpp

OBJ = $(SRC:.cpp=.o)

NAME = test_cpplua

CC = g++

CFLAGS = -Wall -Wextra -llua

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all:	$(NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all
