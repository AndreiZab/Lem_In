/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:24:25 by larlyne           #+#    #+#             */
/*   Updated: 2019/06/27 14:24:42 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_lem_in.h"

static t_link	*ft_link_new(t_room *room)
{
	t_link	*link;
	t_link	*last;

	if (room == NULL)
		return (NULL);
	if ((link = (t_link*)ft_memalloc(sizeof(t_link))) == NULL)
		return (NULL);
	if (room->links == NULL)
		room->links = link;
	else
	{
		last = room->links;
		while (last->next != NULL)
			last = last->next;
		last->next = link;
	}
	return (link);
}

void			ft_link_set(t_room *room1, t_room *room2)
{
	t_link	*link;

	link = ft_link_new(room1);
	link->room = room2;
	link = ft_link_new(room2);
	link->room = room1;
	++room1->links_count;
	++room2->links_count;
}
