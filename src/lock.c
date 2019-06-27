/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:25:03 by larlyne           #+#    #+#             */
/*   Updated: 2019/06/27 15:40:01 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_lem_in.h"

static void	ft_lock_path(t_lemin *li, t_path *path)
{
	t_room	*room;
	int		length;

	length = 0;
	room = path->end;
	room->path_next = li->end_room;
	while (room && room->path_prev)
	{
		++length;
		room->path_prev->path_next = room;
		room->lock = -1;
		room = room->path_prev;
	}
	path->length = length;
	li->mean_length += length;
}

void		ft_lock_paths(t_lemin *li)
{
	t_path	*path;

	li->mean_length = li->ants;
	path = li->paths;
	while (path)
	{
		ft_lock_path(li, path);
		path = path->next;
		++li->paths_count;
	}
}
