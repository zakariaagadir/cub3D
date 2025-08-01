/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:40:21 by zmounji           #+#    #+#             */
/*   Updated: 2025/07/31 15:46:39 by zmounji          ###   ########.fr       */
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

void    put_walls(t_elements  *element)
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

int main(int ac, char ** argv)
{
    t_elements  *element;

    element = getter();
    parcing_mn(ac, argv);
    put_walls(element);
    print_map(element);
    // deb_map();
    element->mlx = mlx_init();
    element->wind = mlx_new_window(element->mlx, 800, 600, "Cube3D");
    element->img = mlx_new_image(element->mlx, 800, 600);
    element->addr = mlx_get_data_addr(element->img, &element->bits_per_px, &element->line_len, &element->endian);
    ray_casting(element);
    mlx_hook(element->wind, 2, 1L<<0, event_handeler, element);
    mlx_loop(element->mlx);
    return (0);
}
