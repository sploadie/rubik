# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/20 16:35:37 by tgauvrit          #+#    #+#              #
#    Updated: 2016/05/12 19:39:15 by tgauvrit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				rubik

CC =				clang++

FLAGS =				-Wall -Werror -Wextra

HEADERS =			-I includes/ -I /usr/local/opt/ncurses/include

SRC_DIR =			srcs/

COMPILED_DIR_NAME =	compiled
COMPILED_DIR =		./$(COMPILED_DIR_NAME)/

FILENAMES =			main Screen

COMPILED_PATHS :=	$(addsuffix .o,$(FILENAMES))
COMPILED_PATHS :=	$(addprefix $(COMPILED_DIR),$(COMPILED_PATHS))

all: $(NAME)

$(NAME): $(COMPILED_PATHS)
	$(CC) -o $(NAME) $(FLAGS) -lncurses $(HEADERS) $(COMPILED_PATHS)

$(COMPILED_PATHS): $(COMPILED_DIR)%.o: $(SRC_DIR)%.cpp
	@/bin/mkdir -p $(COMPILED_DIR)
	$(CC) -c $(FLAGS) $(HEADERS) $< -o $@

clean:
	-/bin/rm -f $(COMPILED_PATHS)
	/usr/bin/find . -name "$(COMPILED_DIR_NAME)" -maxdepth 1 -type d -empty -delete

fclean: clean
	-/bin/rm -f $(NAME)

re: fclean all
