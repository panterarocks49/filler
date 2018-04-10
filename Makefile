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

NAME = fdf
RM = /bin/rm -f
CFLAGS = -Wall -Wextra -Werror

# fdf
FILES = main render read image mat_utils transformations map key_hooks error vert color
FDF_INC = -I ./includes/
SRC_DIR = ./src/
CFILES = $(patsubst %, $(SRC_DIR)%.c, $(FILES))
OFILES = $(patsubst %, %.o, $(FILES))

# mlx lib
MLX_DIR = ./minilibx_macos/
MLX_LIB	= $(addprefix $(MLX_DIR), mlx.a)
MLX_INC = -I $(MLX_DIR)
MLX_LINK = -L $(MLX_DIR) -l mlx -framework OpenGL -framework AppKit

# libft lib
LFT_DIR = ./libft/
LFT_LIB = $(addprefix $(LFT_DIR), ft.a)
LFT_INC = -I $(LFT_DIR)
LFT_LINK = -L $(LFT_DIR) -l ft

.PHONY: all clean fclean re

all: $(MLX_LIB) $(LFT_LIB) $(NAME)

$(OFILES):
	@gcc $(CFLAGS) $(FDF_INC) $(MLX_INC) $(LFT_INC) -c $(CFILES)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(LFT_LIB):
	@make -C $(LFT_DIR)

$(NAME): $(OFILES)
	@gcc $(CFLAGS) $(OFILES) $(MLX_LINK) $(LFT_LINK) -o $(NAME)

clean:
	@$(RM) $(OFILES)
	@make -C $(LFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LFT_DIR) fclean

re: fclean all

rel:
	@$(RM) $(NAME)
	@$(RM) $(OFILES)
	@make