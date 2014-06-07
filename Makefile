##
## Makefile for Makefile in /home/Epitech
##
## Made by dellam_a
## Login   <dellam_a@epitech.net>
##
## Started on  Sun Mar  9 03:35:24 2014 Adrien
## Last update Fri Jun  6 10:52:11 2014 Jean Gravier
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
			Menu.cpp \
			Input.cpp \
			Console.cpp \
			IA.cpp \
			LuaCommunication.cpp \
			Spawn.cpp \
			ModelFactory.cpp \
			ItemFactory.cpp \
			Text.cpp \
			Sound.cpp
			# Widget.cpp

OBJDIR		=	obj/
SRCDIR		=	src/
OBJS		=	$(addprefix $(OBJDIR), $(SRC:.cpp=.o))

CXXFLAGS	+=	-Wextra -Wall -W -O2 -march=native -g3 -p
LDFLAGS		+=	-L$(LIBGDLDIR)/libs/ -lgdl_gl -lGL -lGLEW -lfbxsdk -llua -lSDL2_mixer -lSDL2 -lpthread -lm -ldl -p -lrt

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
