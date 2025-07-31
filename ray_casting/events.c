#include "../cube.h"

int is_free(double x, double y, char **map)
{
	double PLAYER_RADIUS = 0.4;
	if (map[(int)(y - PLAYER_RADIUS)][(int)(x - PLAYER_RADIUS)] == '1' ||
		map[(int)(y - PLAYER_RADIUS)][(int)(x + PLAYER_RADIUS)] == '1' ||
		map[(int)(y + PLAYER_RADIUS)][(int)(x - PLAYER_RADIUS)] == '1' ||
		map[(int)(y + PLAYER_RADIUS)][(int)(x + PLAYER_RADIUS)] == '1')
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
	render(elem);
	return (0);
}
