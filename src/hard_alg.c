#include "ft_lem_in.h"

static void	ft_delete_inputs(t_room *room, int bfs)
{
	t_link	*lnk;

	if (room->input_count > 1)
	{
		lnk = room->input_links;
		while (lnk)
		{
			if (lnk->linked_room->output_count > 1)
			{
				
			}
			lnk = lnk->next;
		}
	}
}

static void	ft_foreach_bfs(t_rooms *rooms, void (*f)(t_room, int))
{
	int		bfs;
	int		finded_on_this_level;
	t_room	*room;

	bfs = 1;
	while (1)
	{
		finded_on_this_level = 0;
		room = rooms;
		while (room)
		{
			if (room->bfs_level == bfs)
			{
				f(room, bfs);
				finded_on_this_level = 1;
			}	
			room = room->next;
		}
		if (finded_on_this_level == 0)
			return ;
		++bfs;
	}
}

void		ft_hard_alg(t_lemin	*li)
{

}