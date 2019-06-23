#include "ft_lem_in.h"

static void	ft_link_unset_rooms(t_room *from, t_room *to, char unset_type)
{
	ft_link_unset_dir(from, to);
	if (unset_type == FT_ALL_LINK)
		ft_link_unset_dir(to, from);
		
}

static void	ft_set_directions(t_lemin *li)
{
	t_room	*room;
	t_link	*lnk;
	t_room	*linked_room;

	room = li->rooms;
	while (room)
	{
		lnk = room->input_links;
		while (lnk)
		{
			linked_room = lnk->linked_room;
			if (linked_room->bfs_level == room->bfs_level)
				ft_link_unset_rooms(linked_room, room, FT_ALL_LINK);
			else if (linked_room->bfs_level < room->bfs_level)
				ft_link_unset_rooms(room, linked_room, FT_DIRECTION);
				
			lnk = lnk->next;
		}
		room = room->next;
	}
}

void		ft_show_links(t_room *room)
{
	t_link	*lnk;

	lnk = room->input_links;
	while (lnk)
	{
		ft_putstr(room->name);
		ft_putstr(" <- ");
		ft_putstr(lnk->linked_room->name);
		ft_putchar('\n');
		lnk = lnk->next;
	}
	lnk = room->output_links;
	while (lnk)
	{
		ft_putstr(room->name);
		ft_putstr(" -> ");
		ft_putstr(lnk->linked_room->name);
		ft_putchar('\n');
		lnk = lnk->next;
	}
}

static t_room	*ft_path_start_room(t_lemin *li, t_room *room)
{
	while (room->input_links->linked_room != li->start_room)
		room = room->input_links->linked_room;
	return (room);
}

static int		ft_find_shortest(t_lemin *li)
{
	int		min_len;
	t_room	*room;
	t_link	*lnk;

	room = NULL;
	min_len = INT_MAX;
	lnk = li->end_room->input_links;
	while (lnk)
	{
		if (lnk->linked_room->bfs_level + 1 < min_len)
		{
			min_len = lnk->linked_room->bfs_level + 1;
			room = lnk->linked_room;
		}
		lnk = lnk->next;
	}
	if (min_len >= li->ants)
	{
		ft_path_new(&li->paths, ft_path_start_room(li, room), room, min_len);
		return (1);
	}
	return (0);
}


int			ft_solution(t_lemin *li)
{
	int		err;
	t_room	*room;

	if ((err = ft_bfs(li)) != FT_OK)
		return (err);
	ft_set_directions(li);
	if (ft_find_shortest(li))
		return (FT_OK);
	
	return (err);
}