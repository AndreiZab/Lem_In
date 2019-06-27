#include "../include/ft_lem_in.h"

void		ft_collision_clear(t_lemin *li)
{
	while (li->collisions->prev)
	{
		li->collisions = li->collisions->prev;
		free(li->collisions->next);
		li->collisions->next = NULL;
	}
}

static void	ft_calculate_paths(t_lemin *li)
{
	t_path	*path;
	t_room	*room;
	int		length;

	path = li->paths;
	while (path)
	{
		room = path->end;
		length = 1;
		while (room && room->path_prev)
		{
			room = room->path_prev;
			++length;
		}
		path->length = length;
		li->mean_length += length;
		path = path->next;
	}
}

static int	ft_make_collision(t_collision *collisions, int lock)
{
	while (lock != 0)
	{
		while (lock != collisions->state)
			collisions = collisions->prev;
		lock = collisions->id;
		collisions->old_room->path_prev = collisions->old_redirect;
	}
	return (0);
}

int		ft_check_collision(t_lemin *li, t_room *room)
{
	int		lock;
	int		new_depth;

	lock = room->lock;
	new_depth = room->weight + room->weight_difference;
	ft_make_collision(li->collisions, lock);
	ft_calculate_paths(li);
}