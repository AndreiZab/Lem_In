/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:30:42 by larlyne           #+#    #+#             */
/*   Updated: 2019/07/03 13:02:30 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_lem_in.h"

int			ft_path_cost(t_lemin *li, int depth)
{
	int				length;
	unsigned int	mean_length;
	int				mod;
	int				ret;
	t_path			*path;

	length = li->mean_length + depth;
	mean_length = length / (li->paths_count + 1);
	mod = length % (li->paths_count + 1);
	ret = li->ants;
	if (li->paths_count != 0 && li->mean_length
	/ li->paths_count < (unsigned int)mean_length)
		return (0);
	path = li->paths;
	while (path)
	{
		ret -= mean_length - path->length + (mod > 0);
		--mod;
		path = path->next;
	}
	return (ret > 0);
}

static void	ft_try_recollision(t_lemin *li, t_room *current, int depth)
{
	t_link	*link;
	t_room	*linked;

	link = current->links;
	while (link)
	{
		linked = link->room;
		if (linked->lock == 0 && linked != li->start_room)
		{
			linked->lock = li->collisions_i;
			if (linked->weight > depth || linked->weight == 0)
			{
				linked->weight = depth;
				linked->weight_difference = current->weight_difference;
				linked->path_prev = current;
			}
		}
		link = link->next;
	}
}

static void	ft_collision_keep(t_lemin *li, t_room *room, t_room *coll_room)
{
	t_collision		*coll;

	coll = li->collisions;
	coll->old_room = coll_room;
	coll->old_redirect = coll_room->path_prev;
	coll->next = (t_collision*)ft_memalloc(sizeof(t_collision));
	coll->state = li->collisions_i;
	coll->to_redirect = room;
	coll->id = room->lock;
	coll->next->prev = coll;
	li->collisions = coll->next;
}

void		ft_collision(t_lemin *li, t_room *room, t_room *coll_room,
				int depth)
{
	t_room	*current;
	int		next_depth;

	next_depth = depth + 1;
	current = coll_room->path_prev;
	++li->collisions_i;
	while (current->path_prev && !current->path_next->closed)
	{
		current->lock = li->collisions_i;
		current->weight_difference = next_depth - depth - 2;
		ft_try_recollision(li, current, next_depth);
		--next_depth;
		current = current->path_prev;
	}
	li->depth = next_depth + 1;
	coll_room->closed = 1;
	ft_collision_keep(li, room, coll_room);
}
