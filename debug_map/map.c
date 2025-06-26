/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:16:13 by zmounji           #+#    #+#             */
/*   Updated: 2025/06/26 18:43:11 by zmounji          ###   ########.fr       */
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
    t_elements *element = getter();
    char **map = element->map->map;
    int player_row = (int)element->player->y;
    int player_col = (int)element->player->x;
    int i, j;
    int tile_size = 8; // Smaller tile size for the minimap
    int screen_x = 10; // Offset X on the window (e.g. top-left corner)
    int screen_y = 10; // Offset Y on the window

    int start_row = player_row - 50;
    int end_row = player_row + 50;
    int start_col = player_col - 50;
    int end_col = player_col + 50;

    for (i = start_row; i <= end_row; i++)
    {
        for (j = start_col; j <= end_col; j++)
        {
            if (i >= 0 && j >= 0 && i < element->map->rows && j < element->map->colomns)
            {
                if (map[i][j] == '1')
                {
                    mlx_put_image_to_window(
                        element->drawing->mlx,
                        element->drawing->win,
                        element->drawing->wall_img,
                        screen_x + (j - start_col) * tile_size,
                        screen_y + (i - start_row) * tile_size
                    );
                }
                // printf("hello\n");
                if ((i == 6) && (j == 16))
                {
                    mlx_put_image_to_window(
                        element->drawing->mlx,
                        element->drawing->win,
                        element->drawing->player_img,
                        screen_x + (j - start_col) * tile_size,
                        screen_y + (i - start_row) * tile_size
                    );
                }
            }
        }
    }
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
