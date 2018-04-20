# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrown <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/05 14:45:29 by jbrown            #+#    #+#              #
#    Updated: 2018/03/10 19:01:23 by jbrown           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = jbrown.filler
RM = /bin/rm -f

FLAGS = -Wall -Wextra -Werror

# filler
FILES = main read check place heatmap util
INCLUDE = -I ./include/
SRC_DIR = ./src/
OBJ_DIR := ./obj/
CFILES = $(patsubst %, $(SRC_DIR)%.c, $(FILES))
OFILES = $(patsubst %, $(OBJ_DIR)%.o, $(FILES))

# libftprintf lib
LFT_DIR = ./libftprintf/
LFT_LIB = $(addprefix $(LFT_DIR), ftprintf.a)
LFT_INC = -I $(LFT_DIR)/include/
LFT_LINK = -L $(LFT_DIR) -l ftprintf

.PHONY: all clean fclean re

all: $(LFT_LIB) $(NAME)

$(LFT_LIB):
	@make -C $(LFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo [INFO] Filler Object Files Directory Created

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@gcc $(FLAGS) $(INCLUDE) $(LFT_INC) -o $@ -c $<
	@echo [INFO] Compiling $< into $@

$(NAME): $(OBJ_DIR) $(OFILES)
	@gcc $(FLAGS) $(OFILES) $(LFT_LINK) -o $(NAME)
	@echo [INFO] Filler Binary Created

clean:
	@rm -rf $(OBJ_DIR)
	@echo [INFO] Filler Object Files Directory Destroyed
	@make -C $(LFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@echo [INFO] Filler Binary Destroyed
	@make -C $(LFT_DIR) fclean

re: fclean all
