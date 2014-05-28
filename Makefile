##
## Makefile for Makefile in /home/Epitech
##
## Made by dellam_a
## Login   <dellam_a@epitech.net>
##
## Started on  Sun Mar  9 03:35:24 2014 Adrien
## Last update Wed May 28 22:44:39 2014 luc sinet
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
			HealthItem.cpp \
			Entity.cpp \
			Settings.cpp \
			Save.cpp \
			Box.cpp \
			Item.cpp \
			ABomb.cpp \
			Bomb.cpp \
			Flame.cpp \
			ACharacter.cpp \
			Player.cpp \
			Map.cpp \
			Input.cpp \
			Console.cpp \
			IA.cpp \
			LuaCommunication.cpp \
			Spawn.cpp \
			ModelFactory.cpp \
			ItemFactory.cpp \
			Text.cpp

OBJDIR		=	obj/
SRCDIR		=	src/
OBJS		=	$(addprefix $(OBJDIR), $(SRC:.cpp=.o))

CXXFLAGS	+=	-Wextra -Wall -W -O2 -march=native -g3
LDFLAGS		+=	-L$(LIBGDLDIR)/libs/ -lgdl_gl -lGL -lGLEW -lrt -lfbxsdk -llua -lSDL2 -lpthread -lm -ldl

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
