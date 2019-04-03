# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/22 13:30:54 by lvasseur          #+#    #+#              #
#    Updated: 2019/04/02 16:31:32 by lvasseur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: make all clean fclean re

NAME = ft_vox
CC = clang++

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/
LIB_PATH = ./

GCC_FLGS = -Wall -Wextra -Werror
GCC_LIBS = -std=c++11 -lpthread -lglfw -framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo -lm -lglew
SRC_NAME = main.cpp ChunkHandler.cpp Chunk.cpp Player.cpp Window.cpp shaders.cpp Texture.cpp MapGeneration.cpp FrustumCulling.cpp
OBJ_NAME = $(SRC_NAME:.cpp=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(GCC_FLGS) $(INC) $(OBJ) $(GCC_LIBS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	mkdir -p $(OBJ_PATH)
	$(CC) $(GCC_FLGS) -std=c++11 $(INC) -o $@ -c $<

clean:
	rm -fv $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -fv $(NAME)

re: fclean all
