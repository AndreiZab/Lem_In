#include "ft_lem_in.h"

static void		ft_add_move(t_lstr *lstr, t_room *from, t_room *to)
{
	to->ant = from->ant;
	ft_lstr_insert_c(lstr, 'L', 1, lstr->length);
	ft_lstr_insert_s(lstr, ft_itoa(from->ant), lstr->length);
	ft_lstr_insert_c(lstr, '-', 1, lstr->length);
	ft_lstr_insert_s(lstr, to->name, lstr->length);
	ft_lstr_insert_c(lstr, ' ', 1, lstr->length);
	from->ant = 0;
}

static t_room	*ft_previous_room(t_room *room)
{
	t_link	*lnk;
	t_room	*linked;
	int		min_dist;

	if (room->input_count == 0)
		return (NULL);
	min_dist = INT_MAX;
	linked = NULL;
	lnk = room->input_links;
	while (lnk)
	{
		if (room->bfs_level - lnk->linked_room->bfs_level < min_dist)
		{
			min_dist = room->bfs_level - lnk->linked_room->bfs_level;
			linked = lnk->linked_room;
		}
		lnk = lnk->next;
	}
	return (linked);
}

static void		ft_move_ants(t_lemin *li, t_path *path, t_lstr *lstr)
{
	t_room	*room;
	t_room	*prev;

	if (path->end->ant != 0)
	{
		--li->ants_on_a_way;
		ft_add_move(lstr, path->end, li->end_room);
	}
	room = path->end;
	while (room != path->start)
	{
		prev = ft_previous_room(room);
		if (prev->flags & FT_ANT)
			ft_add_move(lstr, prev, room);
		room = prev;
	}
}

static void		ft_spawn_ants(t_lemin *li, t_path *path, t_lstr *lstr)
{
	unsigned int	calc;
	t_path	*pth;

	calc = 0;
	if (path != li->paths)
	{
		pth = li->paths;
		while (pth != path)
		{
			calc += path->length - pth->length;
			pth = pth->next;
		}
	}
	if (li->ants > calc)
	{
		li->start_room->ant = li->ants--;
		++li->ants_on_a_way;
		ft_add_move(lstr, li->start_room, path->start);
	}
}

int				ft_migration(t_lemin *li, t_lstr *lstr)
{
	t_path	*path;

	if (li->paths == NULL)
		return (FT_NO_PATHS);
	while (li->ants != 0 || li->ants_on_a_way != 0)
	{
		path = li->paths;
		while (path)
		{
			ft_move_ants(li, path, lstr);
			ft_spawn_ants(li, path, lstr);
			path = path->next;
		}
		lstr->str[lstr->length - 1] = '\n';
	}
	return (FT_OK);
}