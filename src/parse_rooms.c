/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:59:40 by rhealitt          #+#    #+#             */
/*   Updated: 2019/06/23 18:27:28 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"
# define FT_LINK 99

int		ft_room_atoi(const char *str)
{
	int		i;
	long	numb;

	i = 0;
	while (('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ')
		++i;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		++i;
	numb = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		numb = numb * 10 + (str[i++] - '0');
		if (numb < 0 || numb > 2147483647)
			return (-1);
	}
	return ((int)numb);
}

int 	ft_check_room(char *line)
{
	int i;
	int space;

	i = 0;
	while (line[i] != ' ')
	{
		if (line[i] == '-')
			return (FT_LINK);
		if (line[i++] == '\0')
			return (FT_WRONG_FORMAT);
	}
	space = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' && i++)
			continue;
		if (line[i] == '-')
			return (FT_LINK);
		if (line[i] > 57 || line[i] < 48)
			return (FT_WRONG_FORMAT);
		if (i > 1 && line[i - 1] == ' ' && space++)
			if (ft_room_atoi(line + i) < 0)
				return (FT_WRONG_FORMAT);
		i++;
	}
	if (space != 2)
		return (FT_WRONG_FORMAT);
	return (FT_OK);
}

void		ft_found_flag(t_lemin *li, t_room *room, char flag)
{
	if 	(flag == 'e')
		li->end_room = room;
	if 	(flag == 's')
		li->start_room = room;
}

void		ft_create_room(char *line, t_lemin *li, char flag)
{
	t_room *room;
	int i;
	int space;

	room = ft_room_new(&li->rooms);
	room->flags = flag;
	if (flag == 'e' || flag == 's')
		ft_found_flag(li, room, flag);
	i = -1;
	room->name = ft_strdup(line);
	while (line[++i] != ' ') //даб уже сделал это, поправь Андрей
		room->name[i] = line[i];
	room->name[i] = '\0';
	space = 1;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' && i++)
			continue;
		else if (i > 1 && line[i - 1] == ' ' && space == 1 && space++)
			room->x = ft_room_atoi(line + i);
		else if (i > 1 && line[i - 1] == ' ' && space == 2)
			room->y = ft_room_atoi(line + i);
		i++;
	}
}
int 	ft_parse_rooms(int fd, t_lemin *li, t_lstr *lstr)
{
	char	*line;
	int		status;
	char	flag;
	int j = 8;

	flag = 'm';
	status = FT_NO_ROOMS;
	while (get_next_line(fd, &line) > 0 && j-- > 0)
	{
		if (!ft_strcmp(line, "\0"))
			break ;
		ft_lstr_insert_s(lstr, line, lstr->length);
		if (line[0] == '#' && line[1] != '#')
			continue;
		else if (!ft_strcmp(line, "##start") && (flag = 's') != 0)
			continue ;
		else if (!ft_strcmp(line, "##end") && (flag = 'e') != 0)
			continue ;
		status = ft_check_room(line);
		if (status == FT_OK)
		{
			ft_create_room(line, li, flag);
			flag = 'm';
		}
		else if (status == FT_LINK)
			status = ft_parse_links(line, li);
	}
	return (status);
}
