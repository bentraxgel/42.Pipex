# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seok <seok@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/30 15:46:22 by seok              #+#    #+#              #
#    Updated: 2023/08/02 17:44:52 by seok             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAG = -Wall -Wextra -Werror
NAME = pipex
SRC = main.c multiple.c heredoc.c main_utills.c
OBJ = $(SRC:.c=.o)
OBJ_DIR := obj
OBJ_FILE = $(addprefix $(OBJ_DIR)/, $(OBJ))
LIB_DIR = ./libft
LIB_FLAG = -L $(LIB_DIR) -l ft

BONUS = pipex
SRC_B = main_bonus.c multiple_bonus.c heredoc_bonus.c main_utills_bonus.c
OBJ_B = $(SRC_B:.c=.o)
OBJ_DIR_B := obj_bonus
OBJ_FILE_B = $(addprefix $(OBJ_DIR_B)/, $(OBJ_B))

$(NAME): $(OBJ_FILE)
	make -C $(LIB_DIR)
	$(CC) $(CFLAG) $(LIB_FLAG) -o $(NAME) $(OBJ_FILE)
$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(CC) $(CFLAG) -c $< -o $@

$(BONUS): $(OBJ_FILE_B)
	make -C $(LIB_DIR)
	$(CC) $(CFLAG) $(LIB_FLAG) -o $(NAME) $(OBJ_FILE_B)
$(OBJ_DIR_B) :
	mkdir -p $(OBJ_DIR_B)
$(OBJ_DIR_B)/%.o : %.c | $(OBJ_DIR_B)
	$(CC) $(CFLAG) -c $< -o $@

all : $(NAME)
bonus : $(BONUS)
clean :
	make -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR_B)
fclean : clean
	rm -rf $(LIB_DIR)/libft.a
	rm -rf $(NAME)
re : fclean
	make all
.PHONY : all clean fclean re
