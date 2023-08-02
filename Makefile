# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seok <seok@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/30 15:46:22 by seok              #+#    #+#              #
#    Updated: 2023/08/02 16:57:12 by seok             ###   ########.fr        #
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

$(NAME): $(OBJ_FILE)
	make -C $(LIB_DIR)
	$(CC) $(CFLAG) $(LIB_FLAG) -o $(NAME) $(OBJ_FILE)
$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(CC) $(CFLAG) -c $< -o $@

all : $(NAME)
clean :
	make -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)
fclean : clean
	rm -rf $(LIB_DIR)/libft.a
	rm -rf $(NAME)
re : fclean
	make all
.PHONY : all clean fclean re
