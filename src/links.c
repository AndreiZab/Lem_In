/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:24:25 by larlyne           #+#    #+#             */
/*   Updated: 2019/06/27 15:46:39 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_lem_in.h"

int				ft_split_link(char *line, char **name1, char **name2)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '-')
		{
			*name1 = ft_strdup(line);
			(*name1)[i] = '\0';
			*name2 = ft_strdup(line + i + 1);
			if (*name1 == *name2)
				return (FT_DUP_NAME);
			if (*name1 && *name2 && *name1[0] != '\0' && *name2[0] != '\0')
				return (FT_OK);
		}
		i++;
	}
	return (FT_WRONG_FORMAT);
}

int				ft_search_dup_link(t_room *room1, t_room *room2)
{
	t_link	*link;

	link = room1->links;
	while (link)
	{
		if (link->room == room2)
			return (1);
		link = link->next;
	}
	return (0);
}

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
