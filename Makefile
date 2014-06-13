##
## Makefile for Makefile in /home/Epitech
##
## Made by dellam_a
## Login   <dellam_a@epitech.net>
##
## Started on  Sun Mar  9 03:35:24 2014 Adrien
## Last update Fri Jun 13 13:10:02 2014 
##

NAME		=	bomberman

CC		=	g++

RM		=	rm -f

LIBGDLDIR	+=	./libGDL
WIDGETDIR	=	Widgets
SRCDIR		=	./src

INCDIR		=	-I../Includes/ -I$(LIBGDLDIR)/includes/ -I$(SRCDIR) -I$(SRCDIR)/$(WIDGETDIR)/
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
			StockItem.cpp \
			RangeItem.cpp \
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
			Text.cpp \
			Light.cpp \
			EntityFactory.cpp \
			Sound.cpp \
			Square.cpp \
			Hud.cpp \
			$(WIDGETDIR)/AWidget.cpp \
			$(WIDGETDIR)/NavigationWidget.cpp \
			$(WIDGETDIR)/InputWidget.cpp \
			$(WIDGETDIR)/ImageWidget.cpp \
			$(WIDGETDIR)/TextWidget.cpp \
			$(WIDGETDIR)/TextImgWidget.cpp \
			$(WIDGETDIR)/LaunchWidget.cpp \
			$(WIDGETDIR)/QuitWidget.cpp \
			$(WIDGETDIR)/LoadWidget.cpp \
			$(WIDGETDIR)/LoadGameWidget.cpp \
			$(WIDGETDIR)/ArrowWidget.cpp \
			$(WIDGETDIR)/KeyWidget.cpp \
			$(WIDGETDIR)/NameWidget.cpp \
			Intro.cpp

OBJDIR		=	obj/
SRCDIR		=	src/
OBJS		=	$(addprefix $(OBJDIR), $(SRC:.cpp=.o))

CXXFLAGS	+=	-Wextra -Wall -W -O2 -march=native -g3 -p
CXXFLAGS	+=	$(shell pkg-config --cflags libswscale libavcodec libavformat libavutil)

LDFLAGS		+=	$(shell pkg-config --libs libswscale libavcodec libavformat libavutil)
LDFLAGS		+=	-L$(LIBGDLDIR)/libs/ -lgdl_gl -lGL -lGLEW -lfbxsdk -llua -lSDL2_mixer -lSDL2 -lpthread -lm -ldl -p -lrt

dummy		:=	$(shell test -d $(OBJDIR) || mkdir $(OBJDIR)) \
			$(shell test -d $(SRCDIR) || mkdir $(SRCDIR)) \
			$(shell test -d $(OBJDIR)/$(WIDGETDIR) || mkdir $(OBJDIR)/$(WIDGETDIR))

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
