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
	ray_casting/events.c ray_casting/mini_map.c 

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
