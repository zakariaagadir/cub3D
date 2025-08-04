/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:40:21 by zmounji           #+#    #+#             */
/*   Updated: 2025/08/05 00:51:16 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_elements *getter(void)
{
    static t_elements elements;
    if (elements.map == NULL)
    {
        elements.map = malloc(sizeof(t_map));
        if (!elements.map)
            return (NULL);
        ft_bzero(elements.map, sizeof(t_map));
    }
    return (&elements);
}


t_draw	*getter_draw(void)
{
    static t_draw	draw;

    return (&draw);
}

void    print_map(t_elements *element)
{
    int i;

    i = 0;
    printf("start\n");
    while(i < element->map->rows)
    {
        printf("%s\n", element->map->map[i]);
        i++;
    }
}

void    put_doors(t_elements  *element)
{
    char    **map;
    int     i;
    int     j;
    
    i = 0;
    map = element->map->map;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if(map[i][j] == '0')
            {
                if(map[i+1] && map[i+1][j]=='1' && ((i-1) >= 0) && map[i-1][j]=='1' && i != 0 && i != element->map->colomns && j != 0 && j != element->map->colomns && map[i][j+1] != '1' && (j-1) >= 0 && map[i][j-1] != '1')
                {
                    map[i][j]='D';
                }
                
            }
            if(map[i][j] == '0')
            {
                if(((j-1) >= 0) && map[i][j-1]=='1' && map[i][j+1] && map[i][j+1]=='1' && i != 0 && i != element->map->colomns && j != 0 && j != element->map->colomns && map[i+1] && map[i+1][j] != '1' && (i-1) >= 0 && map[i-1][j] != '1' )
                {
                    map[i][j]='D';
                }
                
            }
            j++;
        }
        i++;
    }
}

void	close_doors(t_elements *elem)
{
	char	**map = elem->map->map;

	int px = (int)(elem->player->x);
	int py = (int)(elem->player->y);

	// Calculate the direction the player is facing
	int dx = (int)round(cos(elem->player->angle));
	int dy = (int)round(sin(elem->player->angle));

	// Check two steps *behind* the player
	int back_x = px - 2 * dx;
	int back_y = py - 2 * dy;

	int map_height = elem->map->rows;
	int map_width = elem->map->colomns;

	// Check vertical (Y)
	if (back_y >= 0 && back_y < map_height &&
		px >= 0 && px < map_width &&
		map[back_y][px] == 'd' && py != back_y)
	{
		map[back_y][px] = 'D';
	}

	// Check horizontal (X)
	if (back_x >= 0 && back_x < map_width &&
		py >= 0 && py < map_height &&
		map[py][back_x] == 'd' && px != back_x)
	{
		map[py][back_x] = 'D';
	}
}


int	loop_work(void *elem)
{
	t_elements	*arg;

	arg = elem;
    close_doors(arg);
	render(arg);
    return (0);
}

int main(int ac, char ** argv)
{
    t_elements  *element;

    element = getter();
    parcing_mn(ac, argv);
    put_doors(element);
    print_map(element);
    // deb_map();
    element->mlx = mlx_init();
    element->wind = mlx_new_window(element->mlx, screen_width, screen_height, "Cube3D");
    element->img = mlx_new_image(element->mlx, screen_width, screen_height);
    element->addr = mlx_get_data_addr(element->img, &element->bits_per_px, &element->line_len, &element->endian);
    ray_casting(element);
    mlx_hook(element->wind, 6, 1L << 6, mouse_move_handler, element);
    mlx_hook(element->wind, 2, 1L<<0, event_handeler, element);
    mlx_loop_hook(element->mlx, loop_work, element);
    mlx_loop(element->mlx);
    return (0);
}
