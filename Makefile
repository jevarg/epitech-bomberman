##
## Makefile for Makefile in /home/Epitech
##
## Made by dellam_a
## Login   <dellam_a@epitech.net>
##
## Started on  Sun Mar  9 03:35:24 2014 Adrien
## Last update Fri May  9 15:57:54 2014 Harold Fritsch
##


NAME		=	bomberman

CC		=	g++

RM		=	rm -f

LIBGDLDIR	+=	./libGDL

INCDIR		=	-I../Includes/ -I$(LIBGDLDIR)/includes/
SRCDIR		=	./
SRC		=	main.cpp \
			GameEngine.cpp \
			Exception.cpp \
			Cube.cpp \
			Model.cpp \
			Camera.cpp \
			Container.cpp \
			AObject.cpp \
			AEntitie.cpp \
			Save.cpp \
			Item.cpp \
			Bomb.cpp \
			Flame.cpp \
			ACharacter.cpp \
			Player.cpp \
			Map.cpp

OBJDIR		=	obj/
SRCDIR		=	src/
OBJS		=	$(addprefix $(OBJDIR), $(SRC:.cpp=.o))

CXXFLAGS	+=	-Wextra -Wall -W -g
LDFLAGS		+=	-L$(LIBGDLDIR)/libs/ -Wl,-whole-archive -lgdl_gl -Wl,-no-whole-archive -lGL -lGLEW -lrt -lfbxsdk -lSDL2 -lpthread -ldl

dummy		:=	$(shell test -d $(OBJDIR) || mkdir $(OBJDIR)) \
			$(shell test -d $(SRCDIR) || mkdir $(SRCDIR))

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) $(CXXFLAGS) $(INCDIR) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LOBJS) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
