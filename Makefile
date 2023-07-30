# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seok <seok@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/30 15:46:22 by seok              #+#    #+#              #
#    Updated: 2023/07/30 16:56:27 by seok             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAG = -Wall -Wextra -Werror
NAME = pipex
SRC = main.c execution.c heredoc.c
OBJ = $(SRC:.c=.o)
OBJ_DIR := obj
OBJ_FILE = $(addprefix $(OBJ_DIR)/, $(OBJ))
LIB_DIR = ./libft
LIB_FLAG = -L $(LIB_DIR) -l ft


all : $(NAME)
# make -C $(LIB_DIR) clean
#	clear

$(NAME): $(OBJ_FILE)
	make -C $(LIB_DIR)
	$(CC) $(CFLAG) $(LIB_FLAG) -o $(NAME) $(OBJ_FILE)
$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
$(OBJ_DIR)/%.o : %.c  $(OBJ_DIR)
	$(CC) $(CFLAG) -c $< -o $@


clean :
	rm -rf $(OBJ_DIR)
fclean : clean
	make -C $(LIB_DIR) fclean
	rm -rf $(NAME)
re : fclean
	make all
.PHONY : all clean fclean re
