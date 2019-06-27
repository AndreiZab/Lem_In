/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   migration.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:26:02 by larlyne           #+#    #+#             */
/*   Updated: 2019/06/27 15:40:01 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_lem_in.h"

static void		ft_starts_set(t_lemin *li)
{
	t_path	*path;
	t_room	*room;

	path = li->paths;
	while (path)
	{
		room = path->end;
		while (room && room != li->start_room &&
			room->path_prev != li->start_room)
			room = room->path_prev;
		path->start = room;
		path = path->next;
	}
}

static int		ft_add_move(t_lstr *lstr, t_room *from, t_room *to, int ant)
{
	char	*ant_str;

	if (ant != 0)
		from->ant = ant;
	to->ant = from->ant;
	ft_lstr_insert_c(lstr, 'L', 1, lstr->length);
	ant_str = ft_itoa(from->ant);
	ft_lstr_insert_s(lstr, ant_str, lstr->length);
	free(ant_str);
	ft_lstr_insert_c(lstr, '-', 1, lstr->length);
	ft_lstr_insert_s(lstr, to->name, lstr->length);
	ft_lstr_insert_c(lstr, ' ', 1, lstr->length);
	from->ant = 0;
	return (1);
}

static void		ft_move_on_path(t_lemin *li, t_lstr *lstr, t_path *path,
					int *ant_i)
{
	t_room	*room;

	room = path->end;
	if (room->ant != 0)
	{
		ft_add_move(lstr, room, li->end_room, 0);
		++li->ants_came;
	}
	if (room->path_prev != li->start_room)
		while ((room = room->path_prev) != NULL && room != li->start_room)
			if (room->ant != 0)
				ft_add_move(lstr, room, room->path_next, 0);
	if (path->order != 0)
	{
		ft_add_move(lstr, li->start_room, path->start, *ant_i);
		++(*ant_i);
		--path->order;
	}
}

static void		ft_sending_calc(t_lemin *li)
{
	t_path	*path;
	int		length;
	int		mean;
	int		mod;
	int		cnt;

	cnt = 0;
	length = 0;
	path = li->paths;
	while (path)
	{
		++cnt;
		length += path->length;
		path = path->next;
	}
	mean = (li->ants + length) / cnt;
	mod = (li->ants + length) % cnt;
	path = li->paths;
	while (path)
	{
		path->order = mean - path->length + (mod > 0 ? mod : 0);
		--mod;
		path = path->next;
	}
}

int				ft_migration(t_lemin *li, t_lstr *lstr)
{
	int		ant;
	t_path	*path;

	ant = 1;
	ft_lstr_insert_c(lstr, '\n', 1, lstr->length);
	ft_starts_set(li);
	if (li->paths->start == li->start_room)
	{
		while (li->ants_came++ < li->ants)
			ft_add_move(lstr, li->start_room, li->end_room, ant++);
		lstr->str[lstr->length - 1] = '\n';
		return (FT_OK);
	}
	ft_sending_calc(li);
	while (li->ants_came < li->ants)
	{
		path = li->paths;
		while (path)
		{
			ft_move_on_path(li, lstr, path, &ant);
			path = path->next;
		}
		lstr->str[lstr->length - 1] = '\n';
	}
	return (FT_OK);
}
