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

int			ft_solution(t_lemin *li)
{
	int		err;
	t_room	*room;

	if ((err = ft_bfs(li)) != FT_OK)
		return (err);
	ft_set_directions(li);
	room = li->rooms;
	while (room)
	{
		ft_putstr("BFS_level of ");
		ft_putstr(room->name);
		ft_putstr(" = ");
		ft_putnbr(room->bfs_level);
		ft_putchar('\n');
		ft_show_links(room);
		room = room->next;
	}
	err = FT_OK;
	return (err);
}