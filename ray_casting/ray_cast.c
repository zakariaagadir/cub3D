#include "../cube.h"

void	put_pixel_to_image2(t_elements *elem, int x, int y, int color)
{
	char	*dst;
	if (x < 0 || y < 0 || x >= screen_width || y >= screen_height)
		return ;
	if(color != 0x000000)
	{
		dst = elem->addr + (y * elem->line_len + x * (elem->bits_per_px / 8));
		*(unsigned int *)dst = color;

	}
}

void	put_pixel_to_image(t_elements *elem, int x, int y, int color)
{
	char	*dst;
	if (x < 0 || y < 0 || x >= screen_width || y >= screen_height)
		return ;

	dst = elem->addr + (y * elem->line_len + x * (elem->bits_per_px / 8));
	*(unsigned int *)dst = color;
}

void	get_player_direction(t_elements *elem)
{
	int	p_x;
	int	p_y;

	p_x = (int)(elem->player->x);
	p_y = (int)(elem->player->y);
	if (elem->map->map[p_y][p_x] == 'N')
		elem->player->angle = -(PI / 2);
	else if (elem->map->map[p_y][p_x] == 'S')
		elem->player->angle = (PI / 2);
	else if (elem->map->map[p_y][p_x] == 'E')
		elem->player->angle = 0;
	else if (elem->map->map[p_y][p_x] == 'W')
		elem->player->angle = PI;
}

void	get_player_pos(t_elements *elem)
{
	int	x;
	int	y;

	y = 0;
	while (elem->map->map[y])
	{
		x = 0;
		while (elem->map->map[y][x])
		{
			if (elem->map->map[y][x] == 'N' || elem->map->map[y][x] == 'S' 
			|| elem->map->map[y][x] == 'W' || elem->map->map[y][x] == 'E')
			{
				elem->player->x = x + 0.5;
				elem->player->y = y + 0.5;
				get_player_direction(elem);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	initalize_draw_elems(t_draw *darw, int i, t_elements *elem)
{
	darw->ray_angle = darw->start_angle + i *  darw->step_angle;
	darw->ray_dir_x = cos(darw->ray_angle);
	darw->ray_dir_y = sin(darw->ray_angle);
	darw->delta_dist_x = fabs(1 / darw->ray_dir_x);
	darw->delta_dist_y = fabs(1 / darw->ray_dir_y);
	darw->map_x = (int)elem->player->x;
	darw->map_y = (int)elem->player->y;
	if (darw->ray_dir_x < 0)
	{
		darw->step_x = -1;
		darw->side_dist_x = (elem->player->x - darw->map_x) * darw->delta_dist_x;
	}
	else
	{
		darw->step_x = 1;
		darw->side_dist_x = (darw->map_x + 1.0 - elem->player->x) * darw->delta_dist_x;
	}
	if (darw->ray_dir_y < 0)
	{
		darw->step_y = -1;
		darw->side_dist_y = (elem->player->y - darw->map_y) * darw->delta_dist_y;
	}
	else
	{
		darw->step_y = 1;
		darw->side_dist_y = (darw->map_y + 1.0 - elem->player->y) * darw->delta_dist_y;
	}
}

int	performing_dda(t_draw *draw, t_elements *elem)
{
	int	side;
	char **map;

	map = elem->map->map;
	while (1)
	{
		if (draw->side_dist_x < draw->side_dist_y)
		{
			draw->side_dist_x += draw->delta_dist_x;
			draw->map_x += draw->step_x;
			side = 0;
		}
		else
		{
			draw->side_dist_y += draw->delta_dist_y;
			draw->map_y += draw->step_y;
			side = 1;
		}
		char tile = map[draw->map_y][draw->map_x];
		if (tile == '1' || tile == 'D') // Stop only on wall or door
		{
			draw->door = (tile == 'D');
			return (side);
		}
	}
}

t_texture	*get_texture2(t_elements *elem, t_draw *draw)
{
	if(draw->enemy == 1)
	{
		return (&elem->textures[5]);
	}
	if(draw->door == 1)
	{
		return (&elem->textures[4]);
	}
	if (draw->side == 0) // Hit a vertical wall (East or West)
	{
		if (draw->ray_dir_x > 0)
			return (&elem->textures[0]);
		else
			return (&elem->textures[1]);
	}
	else // Hit a horizontal wall (North or South)
	{
		if (draw->ray_dir_y > 0)
			return (&elem->textures[2]);
		else
			return (&elem->textures[3]);
	}
}

t_texture	*get_texture(t_elements *elem, t_draw *draw)
{
	if(draw->door == 1)
		return (&elem->textures[4]);
	if (draw->side == 0) // Hit a vertical wall (East or West)
	{
		if (draw->ray_dir_x > 0)
			return (&elem->textures[0]);
		else
			return (&elem->textures[1]);
	}
	else // Hit a horizontal wall (North or South)
	{
		if (draw->ray_dir_y > 0)
			return (&elem->textures[2]);
		else
			return (&elem->textures[3]);
	}
}

long	get_texture_pixel(t_texture *tex, int x, int y)
{
	int	pixels_per_line;
	int	color;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0); // prevent out-of-bounds access
	pixels_per_line = tex->line_len / 4; // since each pixel is 4 bytes
	color = tex->addr[y * pixels_per_line + x];
	return (color & 0xFFFFFF); // remove alpha if present
}


long get_color2(t_elements *elem, t_draw draw, int y)
{
	t_texture	*textu;
	double		wallx;
	int			tex_x;
	int			tex_y;
	int			h;


	textu = get_texture2(elem, &draw);
	if (draw.side == 0)
		wallx = elem->player->y + draw.dist_to_wall * draw.ray_dir_y;
	else
		wallx = elem->player->x + draw.dist_to_wall * draw.ray_dir_x;
	wallx -= floor(wallx); // keep only fractional part
	tex_x = (int)(wallx * textu->width);
	if ((draw.side == 0 && draw.ray_dir_x > 0) || (draw.side == 1 && draw.ray_dir_y < 0))
		tex_x = textu->width - tex_x - 1;
	h = y * 256 - screen_height * 128 + draw.wall_height * 128;
	tex_y = ((h * textu->height) / draw.wall_height) / 256;

	return (get_texture_pixel(textu, tex_x, tex_y));
}

long	get_color(t_elements *elem, t_draw draw, int y)
{
	t_texture	*textu;
	double		wallx;
	int			tex_x;
	int			tex_y;
	int			h;

	textu = get_texture(elem, &draw);
	if (draw.side == 0)
		wallx = elem->player->y + draw.dist_to_wall * draw.ray_dir_y;
	else
		wallx = elem->player->x + draw.dist_to_wall * draw.ray_dir_x;
	wallx -= floor(wallx); // keep only fractional part
	tex_x = (int)(wallx * textu->width);
	if ((draw.side == 0 && draw.ray_dir_x > 0) || (draw.side == 1 && draw.ray_dir_y < 0))
		tex_x = textu->width - tex_x - 1;
	h = y * 256 - screen_height * 128 + draw.wall_height * 128;
	tex_y = ((h * textu->height) / draw.wall_height) / 256;

	return (get_texture_pixel(textu, tex_x, tex_y));
}

void	drawing(t_elements *elem, double dist, int i, t_draw draw)
{
	int		wall_top;
	int		wall_bottom;
	int		y;
	long	color;

	draw.wall_height = (int)(screen_height / dist);
	wall_top = (screen_height / 2) - (draw.wall_height / 2);
	wall_bottom = (screen_height / 2) + (draw.wall_height / 2);
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom > screen_height)
		wall_bottom = screen_height;
	y = wall_top;
	while (y < wall_bottom)
	{
		color = get_color(elem, draw, y);
		put_pixel_to_image(elem, i, y, color);
		y++;
	}
}

void	draw_pistol(t_elements *elem)
{
	draw_sprite(elem, &elem->enemy->textures[elem->j], (int) screen_width / 2, (int) screen_height - 100, 400);
}

void	start_3d_view(t_elements *elem)
{
	int		i;
	t_draw	draw;

	i = 0;
	draw.start_angle = elem->player->angle - (fov / 2.0);
	draw.step_angle = fov / screen_width;
	while (i < screen_width)
	{
		initalize_draw_elems(&draw, i, elem);
		draw.side = performing_dda(&draw, elem);
		double dist_for_height;
		double dist_for_tex;
		if (!draw.side)
			dist_for_tex = (draw.map_x - elem->player->x + (1 - draw.step_x) / 2.0) / draw.ray_dir_x;
		else
			dist_for_tex = (draw.map_y - elem->player->y + (1 - draw.step_y) / 2.0) / draw.ray_dir_y;
		dist_for_height = dist_for_tex * cos(draw.ray_angle - elem->player->angle);

		draw.dist_to_wall = dist_for_tex;
		drawing(elem, dist_for_height, i, draw);
		i++;
	}
	draw_pistol(elem);
}

int calculate_enemy_sprite_size(double distance)
{
	if (distance == 0)
		return screen_height;
	return (int)(screen_height / distance); // 64 can be your enemy’s sprite height or a scaling constant
}

void draw_sprite(t_elements *elem, t_texture *tex, int screen_x, int screen_y, int size)
{
    int first_pixel_y = tex->height;
    int last_pixel_y = 0;

    // Find top and bottom bounds of non-transparent pixels
    for (int y = 0; y < tex->height; y++)
    {
        for (int x = 0; x < tex->width; x++)
        {
            int color = get_texture_pixel(tex, x, y);
            if ((color & 0x00FFFFFF) != 0x00000000) // not transparent
            {
                if (y < first_pixel_y) first_pixel_y = y;
                if (y > last_pixel_y)  last_pixel_y = y;
            }
        }
    }

    int cropped_height = last_pixel_y - first_pixel_y + 1;

    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            int tex_x = (x * tex->width) / size;
            int tex_y = first_pixel_y + ((y * cropped_height) / size);
            int color = get_texture_pixel(tex, tex_x, tex_y);

            if ((color & 0x00FFFFFF) == 0x00000000) 
                continue;

            int draw_x = screen_x - size / 2 + x;
            int draw_y = screen_y - size / 2 + y;

            if (draw_x >= 0 && draw_x < screen_width &&
                draw_y >= 0 && draw_y < screen_height)
            {
                put_pixel_to_image(elem, draw_x, draw_y, color);
            }
        }
    }
}

// void draw_enemies(t_elements *elem)
// {
// 	t_enemy *enemy = elem->enemy;

// 	double dx = enemy->x - elem->player->x;
// 	double dy = enemy->y - elem->player->y;
// 	double distance = sqrt(dx * dx + dy * dy);

// 	if (distance < 0.2 || distance > MAX_DRAW_DISTANCE)
// 		return;

// 	double angle = atan2(dy, dx) - elem->player->angle;
// 	if (fabs(angle) > (fov / 2)) // out of FOV
// 		return;
	
// 	double angle_diff = atan2(dy, dx) - elem->player->angle;
// 	while (angle_diff > PI) angle_diff -= 2 * PI;
// 	while (angle_diff < -PI) angle_diff += 2 * PI;
		
// 	if (fabs(angle_diff) > (fov / 2))
// 		return;

// 	int screen_x = (int)((angle_diff / (fov / 2)) * (screen_width / 2)) + (screen_width / 2);
// 	int screen_y = screen_height / 2;
// 	int size = calculate_enemy_sprite_size(distance);

// 	draw_sprite(elem, &enemy->textures, screen_x, screen_y, size);
// }


void	render(t_elements *elem)
{
	int	ceiling_color;
	int	floor_color;
	int	color;
	int	y;
	int	x;

	ceiling_color = (elem->c->a << 16) | (elem->c->b << 8) | elem->c->c;
	floor_color = (elem->f->a << 16) | (elem->f->b << 8) | elem->f->c;
	y = 0;
	while (y < screen_height)
	{
		if (y < screen_height / 2)
			color = ceiling_color;
		else
			color = floor_color;
		x = -1;
		while (++x < screen_width)
		{
			put_pixel_to_image(elem, x, y, color);
		}
		y++;
	}
	start_3d_view(elem);
	draw_mini_map(elem);
	mlx_put_image_to_window(elem->mlx, elem->wind, elem->img, 0, 0);
}

void	load_enemy_textures(t_elements *elem)
{
	elem->enemy->textures[0].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/enemy/frame07.xpm", &elem->enemy->textures[0].width, &elem->enemy->textures[0].height);
	elem->enemy->textures[1].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/enemy/frame08.xpm", &elem->enemy->textures[1].width, &elem->enemy->textures[1].height);
	elem->enemy->textures[2].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/enemy/frame09.xpm", &elem->enemy->textures[2].width, &elem->enemy->textures[2].height);
	elem->enemy->textures[3].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/enemy/frame10.xpm", &elem->enemy->textures[3].width, &elem->enemy->textures[3].height);
	elem->enemy->textures[4].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/enemy/frame11.xpm", &elem->enemy->textures[4].width, &elem->enemy->textures[4].height);
	elem->enemy->textures[5].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/enemy/frame12.xpm", &elem->enemy->textures[5].width, &elem->enemy->textures[5].height);
	elem->enemy->textures[6].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/enemy/frame13.xpm", &elem->enemy->textures[6].width, &elem->enemy->textures[6].height);
	elem->enemy->textures[7].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/enemy/frame14.xpm", &elem->enemy->textures[7].width, &elem->enemy->textures[7].height);
	elem->enemy->textures[8].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/enemy/frame15.xpm", &elem->enemy->textures[8].width, &elem->enemy->textures[8].height);
	elem->enemy->textures[9].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/enemy/frame16.xpm", &elem->enemy->textures[9].width, &elem->enemy->textures[9].height);
}

void	fill_addr(t_elements *elem)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		if (!elem->textures[i].img_ptr)
		{
			printf ("Failed to load texture n : %d\n", i);
			exit (1);//need to free all the memory before exiting, attention |:
		}
		elem->textures[i].addr = (int *)mlx_get_data_addr(elem->textures[i].img_ptr,
			&elem->textures[i].bpp, &elem->textures[i].line_len, &elem->textures[i].endian);
	}
	i = -1;
	while (++i < 10)
	{
		if (!elem->enemy->textures[i].img_ptr)
		{
			printf ("Failed to load texture n : %d\n", i);
			exit (1);//need to free all the memory before exiting, attention |:
		}
		elem->enemy->textures[i].addr = (int *)mlx_get_data_addr(elem->enemy->textures[i].img_ptr,
			&elem->enemy->textures[i].bpp, &elem->enemy->textures[i].line_len, &elem->enemy->textures[i].endian);
		i++;
	}
}

void	load_textures(t_elements *elem)
{
	int	i;

	i = 0;
	elem->textures[0].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/wall_1.xpm", &elem->textures[0].width, &elem->textures[0].height);
	elem->textures[1].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/wall_2.xpm", &elem->textures[1].width, &elem->textures[1].height);
	elem->textures[2].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/wall_3.xpm", &elem->textures[2].width, &elem->textures[2].height);
	elem->textures[3].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/wall_4.xpm", &elem->textures[3].width, &elem->textures[3].height);
	elem->textures[4].img_ptr = mlx_xpm_file_to_image(elem->mlx,
		"textures/door.xpm", &elem->textures[4].width, &elem->textures[4].height);
	load_enemy_textures(elem);
	fill_addr(elem);
}


void	ray_casting(t_elements *elem)
{
	if (!elem->player)
		elem->player = malloc (sizeof(t_player));
	get_player_pos(elem);
	load_textures(elem);
	render(elem);
}
