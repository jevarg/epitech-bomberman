##
## Makefile for Makefile in /home/sinet_l/Documents/project/bomberman
## 
## Made by luc sinet
## Login   <sinet_l@epitech.net>
## 
## Started on  Mon Apr 28 10:00:11 2014 luc sinet
## Last update Mon Apr 28 10:03:03 2014 luc sinet
##

NAME		= bomberman

CC		= g++
RM		= rm -f

CXXFLAGS	+= -Wall -W -Wextra -g
LDFLAGS		=

INCDIR		= -I./Includes/
SRCDIR		= ./src/
SRC		= main.cpp

OBJDIR		= ./obj/
OBJS		= $(addprefix $(OBJDIR), $(SRC:.cpp=.o))

dummy		:= $(shell test -d $(OBJDIR) || mkdir $(OBJDIR))

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) $(CXXFLAGS) $(INCDIR) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(LDFLAGS) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
