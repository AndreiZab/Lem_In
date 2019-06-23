#include "ft_lem_in.h"

static void ft_bfs_set_output_marks(t_room *room, int bfs_mark, t_room *start_room)
{
	t_room	*rm;
	t_link	*lnk;

	lnk = room->output_links;
	while (lnk)
	{
		rm = lnk->linked_room;
		if (rm->bfs_level == 0 && rm != start_room)
			rm->bfs_level = bfs_mark;
		lnk = lnk->next;
	}
}

static int	ft_bfs_set_level(t_lemin *li, int bfs_mark, int *end_reached)
{
	t_room	*room;
	int		counter;

	counter = 0;
	room = li->rooms;
	while (room)
	{
		if (room->bfs_level == bfs_mark)
		{
			++counter;
			if (room == li->end_room)
			{
				room->bfs_level = INT_MAX;
				*end_reached = 1;
			}
			else
			{
				room->bfs_level *= -1;
				ft_bfs_set_output_marks(room, bfs_mark - 1, li->start_room);
			}
		}
		room = room->next;
	}
	return (counter);
}

int			ft_bfs(t_lemin *li)
{
	t_room	*room;
	int		bfs;
	int		end_reached;

	end_reached = 0;
	room = li->start_room;
	bfs = -1;
	ft_bfs_set_output_marks(room, bfs, li->start_room);
	while (ft_bfs_set_level(li, bfs, &end_reached) != 0)
		--bfs;
	return (end_reached ? FT_OK : FT_NO_PATH_TO_END);
}