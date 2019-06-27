/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:27:26 by larlyne           #+#    #+#             */
/*   Updated: 2019/06/27 15:40:01 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_lem_in.h"

static void		ft_set_path_link(t_lemin *li, t_room *from, t_room *to)
{
	if (to->weight == 0 && to != li->start_room && (to->lock != 1 ||
		from == li->start_room))
	{
		to->weight = from->weight + 1;
		to->weight_difference = from->weight_difference;
		to->path_prev = from;
		to->lock = from->lock;
	}
}

static int		ft_set_weights(t_lemin *li, t_room *current)
{
	t_link	*links;
	t_room	*linked;

	if ((links = current->links) == NULL)
		return (0);
	while (links)
	{
		linked = links->room;
		if (linked == li->end_room && (current->lock == 0 ||
			ft_check_collision(li, current)))
			return (1);
		ft_set_path_link(li, current, linked);
		if (current != li->start_room && linked->lock == 1 &&
			(!linked->closed && linked->lock != 1))
		{
			ft_collision(li, current, linked, current->weight);
			return (0);
		}
		links = links->next;
	}
	return (0);
}

static t_room	*ft_step(t_lemin *li, int depth)
{
	t_room	*current;

	--depth;
	current = li->rooms;
	while (current)
	{
		if (current->weight == depth && current->lock != 1 &&
			(current->weight || current == li->start_room))
		{
			if (ft_set_weights(li, current))
				return (current);
		}
		current = current->next;
	}
	return (NULL);
}

static int		ft_find_shortest(t_lemin *li, int it)
{
	static t_room	*room_holder = NULL;
	t_room			*temp;
	t_path			*path;

	li->depth = 1;
	while (li->depth < li->rooms_count)
	{
		if ((temp = ft_step(li, li->depth++)) != NULL)
		{
			if (temp != room_holder && ft_path_cost(li, temp->weight))
			{
				if (room_holder == NULL)
					room_holder = temp;
				//WARNING
				path = ft_path_new(&li->paths);
				path->end = temp;
				path->end->path_next = li->end_room;
				return (1);
			}
			return (0);
		}
	}
	return (0);
}

int				ft_solution(t_lemin *li)
{
	int		i;

	i = 0;
	while (li->paths_count < li->ants && ft_find_shortest(li, i))
	{
		li->collisions_i = 1;
		ft_collision_clear(li);
		ft_lock_paths(li);
		ft_rooms_reset(li->rooms);
		++i;
	}
	ft_collision_clear(li);
	//WARNING
	ft_lock_paths(li);
	if (i)
		return (FT_OK);
	return (FT_NO_PATHS);
}
