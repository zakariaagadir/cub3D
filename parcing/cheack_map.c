/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheack_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:26:41 by zmounji           #+#    #+#             */
/*   Updated: 2025/06/24 16:47:09 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


void check_surronded(t_elements *element)
{
    int i, j;
    char **map = element->map->map;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == ' ')
            {
                // check DOWN
                if (map[i + 1] && map[i + 1][j] != ' ' && map[i + 1][j] != '1')
                {
                    
                    ft_error_el("Map not surrounded by walls (down)");
                }
                
                // check UP
                if (i > 0 && map[i - 1][j] != ' ' && map[i - 1][j] != '1')
                {
                    printf("---> %s\n", map[i]);
                    printf("---> %s\n", map[i - 1]);
                    ft_error_el("Map not surrounded by walls (up)");
                }

                // check LEFT
                if (j > 0 && map[i][j - 1] != ' ' && map[i][j - 1] != '1')
                    ft_error_el("Map not surrounded by walls (left)");

                // check RIGHT
                if (map[i][j + 1] && map[i][j + 1] != ' ' && map[i][j + 1] != '1')
                    ft_error_el("Map not surrounded by walls (right)");
            }
            j++;
        }
        i++;
    }
}


void    cheack_map(void)
{
    t_elements *element;

    element = getter();
    check_surronded(element);
}