##
## Makefile for Makefile in /home/Epitech
##
## Made by dellam_a
## Login   <dellam_a@epitech.net>
##
## Started on  Sun Mar  9 03:35:24 2014 Adrien
## Last update Wed May 21 19:06:50 2014 
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
			Mutex.cpp \
			Condvar.cpp \
			Cube.cpp \
			Model.cpp \
			Camera.cpp \
			ATransformation.cpp \
			Container.cpp \
			AEntity.cpp \
			ALivingEntity.cpp \
			AItem.cpp \
			SpeedItem.cpp \
			Entity.cpp \
			Settings.cpp \
			Save.cpp \
			Item.cpp \
			ABomb.cpp \
			Bomb.cpp \
			Flame.cpp \
			ACharacter.cpp \
			Player.cpp \
			Map.cpp \
			Menu.cpp \
			Input.cpp \
			Spawn.cpp \
			Text.cpp \
			ModelFactory.cpp

OBJDIR		=	obj/
SRCDIR		=	src/
OBJS		=	$(addprefix $(OBJDIR), $(SRC:.cpp=.o))

CXXFLAGS	+=	-Wextra -Wall -W -O2 -march=native -g3 -p
LDFLAGS		+=	-L$(LIBGDLDIR)/libs/ -lgdl_gl -lGL -lGLEW -lrt -lfbxsdk -lSDL2 -lpthread -lm -ldl -p

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
