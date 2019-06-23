#include "ft_lem_in.h"

static int	ft_is_start(t_room *room)
{
	return (room->flags & FT_START);
}

static void ft_bfs_set_output_marks(t_room *room, int bfs_mark)
{
	t_room	*rm;
	t_link	*lnk;

	lnk = room->output_links;
	while (lnk)
	{
		rm = lnk->linked_room;
		if (rm->bfs_level == 0)
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
			if (room->flags & FT_END)
			{
				room->bfs_level = INT_MAX;
				*end_reached = 1;
			}
			else
			{
				room->bfs_level *= -1;
				ft_bfs_set_output_marks(room, bfs_mark - 1);
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
	room = ft_room_get_where(li->rooms, &ft_is_start);
	bfs = -1;
	ft_bfs_set_output_marks(room, bfs);
	while (ft_bfs_set_level(li, bfs, &end_reached) != 0)
		--bfs;
	return (end_reached ? FT_OK : FT_NO_PATH_TO_END);
}