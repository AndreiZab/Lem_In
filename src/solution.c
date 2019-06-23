#include "ft_lem_in.h"

// static void	ft_link_unset_rooms(t_room *from, t_room *to, char unset_type)
// {
// 	int		i;

// 	i = -1;
// 	while (++i < from->input_count)
// 		if (from->input_links[i * 2] == to->index)
// 		{
// 			from->input_links[i * 2 + 1] = FT_DELETED;
// 			break ;
// 		}
// 	if (unset_type == FT_ALL_LINK)
// 	{
// 		i = -1;
// 		while (++i < to->output_count)
// 			if (to->output_links[i * 2] == from->index)
// 			{
// 				to->output_links[i * 2 + 1] = FT_DELETED;
// 				break ;
// 			}
// 	}
// }

// static void	ft_set_directions(t_lemin *li)
// {
// 	t_room	*room;
// 	int		i;
// 	t_room	*linked_room;

// 	room = li->rooms;
// 	while (room)
// 	{
// 		i = -1;
// 		while (++i < room->input_count)
// 		{
// 			linked_room = ft_room_get(li->rooms, room->input_links[i * 2]);
// 			if (linked_room->bfs_level == room->bfs_level)
// 				ft_link_unset_rooms(linked_room, room, FT_ALL_LINK);
// 			else if (linked_room->bfs_level > room->bfs_level)
// 				ft_link_unset_rooms(room, linked_room, FT_DIRECTION);
// 		}
// 		room = room->next;
// 	}
// }

int			ft_solution(t_lemin *li)
{
	int		err;

	//if ((err = ft_bfs(li)) != FT_OK)
	//	return (err);
	//ft_set_directions(li);
	(void)li;
	err = FT_OK;
	return (err);
}