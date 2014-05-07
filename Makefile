##
## Makefile for Makefile in /home/Epitech
##
## Made by dellam_a
## Login   <dellam_a@epitech.net>
##
## Started on  Sun Mar  9 03:35:24 2014 Adrien
## Last update Wed May  7 18:54:07 2014 Jean Gravier
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
			Player.cpp \
			Cube.cpp \
			Camera.cpp \
			ATransformation.cpp \
			Model.cpp

OBJDIR		=	obj/
SRCDIR		=	src/
OBJS		=	$(addprefix $(OBJDIR), $(SRC:.cpp=.o))

CXXFLAGS	+=	-Wextra -Wall -W -g -p
LDFLAGS		+=	-L$(LIBGDLDIR)/libs/ -lgdl_gl -lGL -lGLEW -lrt -lfbxsdk -lSDL2 -lpthread -ldl -p

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
