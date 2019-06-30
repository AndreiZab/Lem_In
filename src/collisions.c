/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:30:36 by larlyne           #+#    #+#             */
/*   Updated: 2019/06/27 20:50:20 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_path			*path;
	t_room			*room;
	unsigned int	length;

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

static int	ft_make_collision(t_collision *collisions, int lock, int old)
{
	while (lock != 0)
	{
		while (lock != collisions->state)
			collisions = collisions->prev;
		lock = collisions->id;
		collisions->old_room->path_prev =
			old ? collisions->old_redirect : collisions->to_redirect;
	}
	return (0);
}

int			ft_check_collision(t_lemin *li, t_room *room)
{
	int				lock;
	unsigned int	new_depth;
	t_collision		*coll;

	lock = room->lock;
	new_depth = room->weight + room->weight_difference + 1;
	ft_make_collision(li->collisions, lock, 0);
	ft_calculate_paths(li);
	coll = li->collisions;
	if (ft_path_cost(li, new_depth) == 0)
		return (ft_make_collision(coll, lock, 1));
	return (1);
}
