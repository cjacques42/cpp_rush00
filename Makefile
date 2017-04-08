# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjacques <cjacques@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/27 10:02:34 by cjacques          #+#    #+#              #
#    Updated: 2017/04/08 15:21:42 by cjacques         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_retro
CC = clang++
CFLAGS = -Wall -Werror -Wextra
OBJ_PATH = obj/
SRC_PATH = src/
SHELL = /bin/bash

SRC_NAME =	main.cpp\
			AGameEntity.cpp\
			Player.cpp\
			Game.cpp\

OBJ_NAME = $(SRC_NAME:.cpp=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@echo -e "\033[32mCompile...\033[0m"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I includes -lncurses
	@echo -e "\033[32mDone\033[0m"

$(OBJ_PATH)%.o:$(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I includes -c $^ -o $@

clean:
	@echo -e "\033[32mClean\033[0m"
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
