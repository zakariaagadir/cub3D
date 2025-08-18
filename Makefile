# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/16 18:51:42 by zmounji           #+#    #+#              #
#    Updated: 2025/08/18 12:06:40 by abifkirn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc 
FLAGS = -Wall -Wextra -Werror -g3

MLX_DIR = ./minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
INCLUDES = -I$(MLX_DIR) # optional, if you include mlx.h with "minilibx-linux/mlx.h"

SRC = main.c parcing/parcing_mn.c parcing/extract_map.c parcing/map.c\
	helpers/get_next_line/get_next_line.c helpers/get_next_line/get_next_line_utils.c\
	helpers/libft/ft_bzero.c parcing/upload_map.c helpers/libft/ft_split.c\
	helpers/libft/ft_atoi.c parcing/cheack_map.c ray_casting/ray_cast.c\
	ray_casting/events.c ray_casting/mini_map.c garbagecolector/ga_collector.c\
	getters.c doors_and_animation.c ray_casting/drawing.c ray_casting/texture.c\
	ray_casting/ray_cast_helper.c ray_casting/moves.c ray_casting/rotation.c

OBJ = ${SRC:.c=.o}

%.o: %.c
	${CC} ${FLAGS} $(INCLUDES) -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${OBJ} $(MLX_FLAGS) -o ${NAME}

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
