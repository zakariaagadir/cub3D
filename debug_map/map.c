/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:16:13 by zmounji           #+#    #+#             */
/*   Updated: 2025/06/26 16:28:09 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


void    set_up_player(void)
{
    t_elements  *element;
    char        **map;
    int         i;
    int         j;
    
    element = getter();
    map = element->map->map;
    i = 0;
    if (!map)
        ft_error_el("mrid f krk\n");
    while (i < element->map->rows)
    {
        j = 0;
        while (j < element->map->colomns)
        {
            if (element->map->map[i][j] == 'N' || element->map->map[i][j] == 'S' || element->map->map[i][j] == 'O' || element->map->map[i][j] == 'e')
            {
                if(element->player)
                    ft_error("one player\n");
                element->player = malloc(sizeof(t_player));
                if (!element->player)
                    ft_error_el("mallo\n");
                ft_bzero(element->player, sizeof(t_player));
                element->player->direction = malloc(2);
                if (!element->player->direction)
                    ft_error_el("malloc\n");
                element->player->direction[0] = map[i][j];
                element->player->direction[1] = '\0';
                element->player->x = i;
                element->player->y = j;
            }
            j++;
        }
        i++;
    }
    
}

void    inisialise_dr(void)
{
    t_elements  *element;
    
    element = getter();
    element->drawing = malloc(sizeof(t_draw));
    if (!element->drawing)
        ft_error_el("malloc\n");
    ft_bzero(element->drawing, sizeof(t_draw));
    element->drawing->mlx = mlx_init();
    element->drawing->player_img = mlx_xpm_file_to_image(element->drawing->mlx, "texture/player_deb.xpm", &(int){0}, &(int){0});
    element->drawing->wall_img = mlx_xpm_file_to_image(element->drawing->mlx, "texture/wall_deb.xpm", &(int){0}, &(int){0});
    element->drawing->win = mlx_new_window(element->drawing->mlx, 1080, 720, "Cub3D");
}

void render_frame(void)
{
    t_elements  *element = getter();
    char        **map = element->map->map;
    int         i, j;

    for (i = 0; i < 30 && i < element->map->rows; i++)
    {
        for (j = 0; j < 50 && j < element->map->colomns; j++)
        {
            if (map[i][j] == '1')
            {
                mlx_put_image_to_window(
                    element->drawing->mlx,
                    element->drawing->win,
                    element->drawing->wall_img,
                    j * 16,
                    i * 16
                );
            }
        }
    }

    // Draw player at appropriate position (optional):
    int px = (int)element->player->x;
    int py = (int)element->player->y;
    mlx_put_image_to_window(
        element->drawing->mlx,
        element->drawing->win,
        element->drawing->player_img, px * 16,
        py * 16
    );
}

void    deb_map(void)
{
    t_elements  *element;

    element = getter();
    set_up_player();
    if (!element->player)
        ft_error_el("player not exist\n");
    printf("player her --> x=%d , y=%d\n",element->player->x, element->player->y);
    inisialise_dr();
    render_frame();
}
