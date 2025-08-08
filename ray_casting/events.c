#include "../cube.h"

int is_free(double x, double y, char **map)
{
	double PLAYER_RADIUS = 0.4;
	if (map[(int)(y - PLAYER_RADIUS)][(int)(x - PLAYER_RADIUS)] == '1' ||
		map[(int)(y - PLAYER_RADIUS)][(int)(x + PLAYER_RADIUS)] == '1' ||
		map[(int)(y + PLAYER_RADIUS)][(int)(x - PLAYER_RADIUS)] == '1' ||
		map[(int)(y + PLAYER_RADIUS)][(int)(x + PLAYER_RADIUS)] == '1' ||
		map[(int)(y - PLAYER_RADIUS)][(int)(x - PLAYER_RADIUS)] == 'D' ||
		map[(int)(y - PLAYER_RADIUS)][(int)(x + PLAYER_RADIUS)] == 'D' ||
		map[(int)(y + PLAYER_RADIUS)][(int)(x - PLAYER_RADIUS)] == 'D' ||
		map[(int)(y + PLAYER_RADIUS)][(int)(x + PLAYER_RADIUS)] == 'D')
		return (0);
	return (1);
}

void	move_forward(t_elements *elem)
{
	double new_x = elem->player->x + cos(elem->player->angle) * MOVE_SPEED;
	double new_y = elem->player->y + sin(elem->player->angle) * MOVE_SPEED;

	if (is_free(new_x, elem->player->y, elem->map->map))
		elem->player->x = new_x;
	if (is_free(elem->player->x, new_y, elem->map->map))
		elem->player->y = new_y;
}

void	move_backward(t_elements *elem)
{
	double new_x = elem->player->x - cos(elem->player->angle) * MOVE_SPEED;
	double new_y = elem->player->y - sin(elem->player->angle) * MOVE_SPEED;

	if (is_free(new_x, elem->player->y, elem->map->map))
		elem->player->x = new_x;
	if (is_free(elem->player->x, new_y, elem->map->map))
		elem->player->y = new_y;
}

void	move_left(t_elements *elem)
{
	double angle = elem->player->angle - PI / 2;
	double new_x = elem->player->x + cos(angle) * MOVE_SPEED;
	double new_y = elem->player->y + sin(angle) * MOVE_SPEED;

	if (is_free(new_x, elem->player->y, elem->map->map))
		elem->player->x = new_x;
	if (is_free(elem->player->x, new_y, elem->map->map))
		elem->player->y = new_y;
}

void	move_right(t_elements *elem)
{
	double angle = elem->player->angle + PI / 2;
	double new_x = elem->player->x + cos(angle) * MOVE_SPEED;
	double new_y = elem->player->y + sin(angle) * MOVE_SPEED;

	if (is_free(new_x, elem->player->y, elem->map->map))
		elem->player->x = new_x;
	if (is_free(elem->player->x, new_y, elem->map->map))
		elem->player->y = new_y;
}

void	rotate_left(t_elements *elem)
{
	elem->player->angle -= ROT_SPEED;
	if (elem->player->angle < 0)
		elem->player->angle += 2 * PI;
}

void	rotate_right(t_elements *elem)
{
	elem->player->angle += ROT_SPEED;
	if (elem->player->angle > 2 * PI)
		elem->player->angle -= 2 * PI;
}

void	oupen_door(t_elements *elem)
{
	char	**map = elem->map->map;

	int px = (int)(elem->player->x);
	int py = (int)(elem->player->y);

	// Calculate the direction the player is facing
	int dx = (int)round(cos(elem->player->angle));
	int dy = (int)round(sin(elem->player->angle));

	int tx = px + dx;
	int ty = py + dy;

	// Check map bounds
	if (ty >= 0 && ty < elem->map->rows && tx >= 0 && tx < elem->map->colomns)
	{
		if (map[ty][tx] == 'D')
		{
			map[ty][tx] = 'd'; // Open the door
			printf("Opened door at [%d][%d]\n", ty, tx);
		}
	}
}

void	shooting(t_elements *elem)
{
	static int i;

	if (i < 1)
		i++;
	else if (elem->j < 9)
	{
		i = 0;
		elem->j++;
	}
	else
	{
		i = 0;
		elem->j = 0;
	}
	// i = 0;
}

int	event_handeler(int code, t_elements *elem)
{
	if (code == 65361) // Left arrow
		rotate_left(elem);
	else if (code == 65363) // Right arrow
		rotate_right(elem);
	else if (code == 'w')
		move_forward(elem);
	else if (code == 's')
		move_backward(elem);
	else if (code == 'a')
		move_left(elem);
	else if (code == 'd')
		move_right(elem);
	else if (code == 'o')
		oupen_door(elem);
	return (0);
}

int	check_button(int code, int x, int y, void *element)
{
	t_elements *elem;
	(void) x; // if you don’t use x and y, avoid unused parameter warnings
    (void) y;
	elem = (t_elements *) element;
	if (code == 1)
		shooting(elem);

	return (0);
}

int	mouse_move_handler(int x, int y, t_elements *elem)
{
	static int last_x = -1;
	int delta_x;

	(void)y;
	if (last_x == -1)
		last_x = x;
	delta_x = x - last_x;
	last_x = x;
	double sensitivity = 0.001;
	elem->player->angle += delta_x * sensitivity;

	// Keep angle in [0, 2π]
	if (elem->player->angle < 0)
		elem->player->angle += 2 * PI;
	else if (elem->player->angle > 2 * PI)
		elem->player->angle -= 2 * PI;
	return (0);
}
