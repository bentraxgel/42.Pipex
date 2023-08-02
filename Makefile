# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seok <seok@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/30 15:46:22 by seok              #+#    #+#              #
#    Updated: 2023/08/02 13:46:29 by seok             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAG = -Wall -Wextra -Werror -g #-fsanitize=address -g3
NAME = pipex
SRC = main.c execution.c heredoc.c #main_utills.c
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

# all 레시피에 libft에 대한 명령어 사용하지 마라 왜냐면 재make했을때 동작이 자꾸 되는게 이상해서요
# 아무것도 안돼야 맞지 않나...?
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
