## on y va a l'arrache

LUASRC = main.lua \
	 global.lua

LUANAME = ia.out

LUA = luac5.2

SRC = 	main.cpp \
	cppLua.cpp

OBJ = $(SRC:.cpp=.o)

CPPNAME = test_cpplua

CC = g++

CFLAGS = -Wall -Wextra -llua

all:	$(CPPNAME)

lua:
	$(LUA) -o $(LUANAME) $(LUASRC)
	@chmod +x $(LUANAME)

$(CPPNAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(CPPNAME) $(OBJ)

cleanlua:
	rm -rf ia.out

cleancpp:
	rm -rf $(OBJ)

fclean:	cleancpp
	rm -rf $(CPPNAME)

re:	fclean all
