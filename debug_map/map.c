/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:16:13 by zmounji           #+#    #+#             */
/*   Updated: 2025/07/05 10:18:55 by abifkirn         ###   ########.fr       */
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
        ft_error_el("mrid f krk\n"); // hatid a mounji hiydst mn be3d hhh
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
                    ft_error_el("malloc\n");
                ft_bzero(element->player, sizeof(t_player));
                element->player->direction = malloc(2);
                if (!element->player->direction)
                    ft_error_el("malloc\n");
                element->player->direction[0] = map[i][j];
                element->player->direction[1] = '\0';
                element->player->x = j;
                element->player->px = ((j * window_py) + (window_py / 2));
                element->player->y = i;
                element->player->py = ((i * window_py) + (window_px / 2));
                element->map->map[i][j] = '0';
            }
            j++;
        }
        i++;
    }
    
}

void *create_colored_image(t_elements  *element, int width, int height, int color)
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     x, y;

    img = mlx_new_image(element->drawing->mlx, width, height);
    if (!img)
        return (NULL);
    
    addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
    y = 0;
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            int pixel_offset = (y * line_length) + (x * (bits_per_pixel / 8));
            *(unsigned int*)(addr + pixel_offset) = color;
            x++;
        }
        y++;
    }
    
    return (img);
}

void *create_circle_image(t_elements *element, int size, int color)
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     x, y;
    int     center_x, center_y;
    int     radius;
    int     distance_squared;

    // Create new image
    img = mlx_new_image(element->drawing->mlx, size, size);
    if (!img)
        return (NULL);
    
    // Get image data address
    addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
    
    // Calculate circle parameters
    center_x = size / 2;
    center_y = size / 2;
    radius = (size / 2) - 1; // Slightly smaller than the tile
    
    // Fill the image with transparent background and yellow circle
    y = 0;
    while (y < size)
    {
        x = 0;
        while (x < size)
        {
            // Calculate distance from center
            int dx = x - center_x;
            int dy = y - center_y;
            distance_squared = (dx * dx) + (dy * dy);
            
            // Calculate pixel position in memory
            int pixel_offset = (y * line_length) + (x * (bits_per_pixel / 8));
            
            // Draw circle
            if (distance_squared <= (radius * radius))
                *(unsigned int*)(addr + pixel_offset) = color;
            else
                *(unsigned int*)(addr + pixel_offset) = 0x00000000; // Transparent
            x++;
        }
        y++;
    }
    
    return (img);
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
    element->drawing->player_img = create_circle_image(element, player_raduis, player_color);
    // element->drawing->player_img = mlx_xpm_file_to_image(element->drawing->mlx, "texture/player_deb.xpm", &(int){0}, &(int){0});
    // element->drawing->wall_img = mlx_xpm_file_to_image(element->drawing->mlx, "texture/wall_deb.xpm", &(int){0}, &(int){0});
    element->drawing->wall_img = create_colored_image(element, window_py, window_px, wall_color);
    element->drawing->win = mlx_new_window(element->drawing->mlx, element->map->colomns * 16, element->map->rows * 16, "Cub3D");
}

void render_frame(void)
{
    t_elements *element = getter();
    char **map = element->map->map;
    int i;
    int j;
    
    i = 0;
    while(i < element->map->rows)
    {
        j = 0;
        while (j < element->map->colomns)
        {
            if (map[i][j] == '1')
            {
                mlx_put_image_to_window(element->drawing->mlx, element->drawing->win, element->drawing->wall_img, j * 16, i * 16);
            }
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(element->drawing->mlx, element->drawing->win, element->drawing->player_img, element->player->px, element->player->py);
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
