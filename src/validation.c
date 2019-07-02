/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:46:04 by rhealitt          #+#    #+#             */
/*   Updated: 2019/06/27 20:50:20 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_lem_in.h"

int			ft_found_flag(t_lemin *li, t_room *room, char flag)
{
	if (flag == FT_START)
	{
		if (li->start_room)
			return (FT_ONE_MORE_START);
		else
			li->start_room = room;
	}
	if (flag == FT_END)
	{
		if (li->end_room)
			return (FT_ONE_MORE_END);
		else
			li->end_room = room;
	}
	return (FT_OK);
}

void		ft_coordinate_room(t_room *room, char *line, int i)
{
	int space;

	space = 1;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' && i++)
			continue;
		else if (i > 1 && line[i - 1] == ' ' && space == 1 && space++)
			room->x = ft_atoi(line + i);
		else if (i > 1 && line[i - 1] == ' ' && space == 2)
			room->y = ft_atoi(line + i);
		i++;
	}
}

int			ft_create_room(char *line, t_lemin *li, char *flag)
{
	t_room	*room;
	int		err;
	int		i;

	room = ft_room_new(li, &li->rooms);
	room->flags = *flag;
	err = ft_found_flag(li, room, *flag);
	i = -1;
	room->name = ft_strdup(line);
	while (line[++i] != ' ')
		room->name[i] = line[i];
	room->name[i] = '\0';
	ft_coordinate_room(room, line, i);
	*flag = FT_NO_FLAGS;
	return (err);
}

static int	ft_parse_ants(int fd, t_lemin *li, t_lstr *lstr)
{
	char	*line;
	int		i;
	int		err;

	err = FT_OK;
	get_next_line(fd, &line);
	ft_string_insert(lstr, line, lstr->length);
	if (line[0] == '#' && line[1] != '#')
		return (ft_parse_ants(fd, li, lstr));
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '-')
			err = FT_NO_ANTS;
		if (i == 0 && line[i] == '+')
			i++;
		if (line[i] > 57 || line[i] < 48)
			err = FT_WRONG_FORMAT;
		i++;
	}
	li->ants = (ft_isint(line)) ? ft_atoi(line) : 0;
	if (li->ants <= 0 || li->ants > 2147483647)
		err = FT_NO_ANTS;
	free(line);
	return (err);
}

int			ft_validation(int fd, t_lemin *li, t_lstr *lstr)
{
	int err;

	err = ft_parse_ants(fd, li, lstr);
	if (err == FT_OK)
	{
		err = FT_NO_DATA;
		err = ft_parse_rooms(fd, li, lstr, err);
	}
	return (err);
}
