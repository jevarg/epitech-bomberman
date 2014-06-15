##
## Makefile for Makefile in /home/Epitech
##
## Made by dellam_a
## Login   <dellam_a@epitech.net>
##
## Started on  Sun Mar  9 03:35:24 2014 Adrien
<<<<<<< HEAD
## Last update Sun Jun 15 09:12:10 2014 luc sinet
=======
## Last update Mon May 12 16:28:27 2014 luc sinet
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
##

NAME		=	bomberman

CC		=	g++

RM		=	rm -f

LIBGDLDIR	+=	./libGDL
<<<<<<< HEAD
LIBAVDIR	=	./libav
WIDGETDIR	=	Widgets
SRCDIR		=	./src

INCDIR		=	-I../Includes/ -I$(LIBGDLDIR)/includes/ -I$(SRCDIR) -I$(SRCDIR)/$(WIDGETDIR)/
=======

INCDIR		=	-I../Includes/ -I$(LIBGDLDIR)/includes/
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
SRCDIR		=	./
SRC		=	main.cpp \
			GameEngine.cpp \
			Exception.cpp \
<<<<<<< HEAD
			Mutex.cpp \
			Condvar.cpp \
=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
			Cube.cpp \
			Model.cpp \
			Camera.cpp \
			ATransformation.cpp \
			Container.cpp \
<<<<<<< HEAD
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
=======
			AEntitie.cpp \
			Settings.cpp \
			Save.cpp \
			Item.cpp \
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
			Bomb.cpp \
			Flame.cpp \
			ACharacter.cpp \
			Player.cpp \
			Map.cpp \
<<<<<<< HEAD
			Menu.cpp \
			Input.cpp \
			Console.cpp \
			IA.cpp \
			Chicken.cpp \
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
			$(WIDGETDIR)/ResWidget.cpp \
			$(WIDGETDIR)/FullScreenWidget.cpp \
			$(WIDGETDIR)/ClickTextWidget.cpp \
			$(WIDGETDIR)/SaveWidget.cpp \
			Intro.cpp
=======
			Input.cpp
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473

OBJDIR		=	obj/
SRCDIR		=	src/
OBJS		=	$(addprefix $(OBJDIR), $(SRC:.cpp=.o))

<<<<<<< HEAD
CXXFLAGS	+=	-Wextra -Wall -W -O2 -march=native -g3
CXXFLAGS	+=	$(shell pkg-config --cflags libswscale libavcodec libavformat libavutil)

LDFLAGS		+=	$(shell pkg-config --libs libswscale libavcodec libavformat libavutil)
LDFLAGS		+=	-L$(LIBGDLDIR)/libs/
LDFLAGS		+=	-lgdl_gl -lGL -lGLEW -lfbxsdk -llua -lSDL2_mixer -lSDL2 -lpthread -lm -ldl -lrt

dummy		:=	$(shell test -d $(OBJDIR) || mkdir $(OBJDIR)) \
			$(shell test -d $(SRCDIR) || mkdir $(SRCDIR)) \
			$(shell test -d $(OBJDIR)/$(WIDGETDIR) || mkdir $(OBJDIR)/$(WIDGETDIR))
=======
CXXFLAGS	+=	-Wextra -Wall -W -O2 -march=native
LDFLAGS		+=	-L$(LIBGDLDIR)/libs/ -lgdl_gl -lGL -lGLEW -lrt -lfbxsdk -lSDL2 -lpthread -ldl -p

dummy		:=	$(shell test -d $(OBJDIR) || mkdir $(OBJDIR)) \
			$(shell test -d $(SRCDIR) || mkdir $(SRCDIR))
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473

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
