/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:59:40 by rhealitt          #+#    #+#             */
/*   Updated: 2019/06/25 17:02:40 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"
# define FT_LINK 99


int		ft_room_atoi(const char *str)
{
	int		i;
	long	numb;
	char	sign;
	char	s;

	i = 0;
	while (('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ')
		++i;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		++i;
	s = sign;
	numb = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		numb = numb * 10 + (str[i++] - '0');
		if (numb < 0)
			return (0);
	}
	if ((numb > 2147483648 && s == -1) || (numb > 2147483647 && s == 1))
		return (0);
	return ((int)numb * sign);
}

int 	ft_check_room(char *line, char flag)
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
	if (flag == FT_ERROR)
		return (FT_WRONG_FORMAT);
	while (line[i] != '\0')
	{
		if (line[i] == ' ' && i++)
			continue;
		if (line[i] == '-' && i > 1 && line[i - 1] != ' ')
			return (FT_LINK);
		if ((line[i] > 57 || line[i] < 48) && line[i] != 45)
			return (FT_WRONG_FORMAT);
		if (i > 1 && line[i - 1] == ' ' && ++space)
			if (ft_room_atoi(line + i) == 0 && line[i] != '0')
				return (FT_WRONG_FORMAT);
		i++;
	}
	if (space != 2)
		return (FT_WRONG_FORMAT);
	return (FT_OK);
}

int			ft_found_flag(t_lemin *li, t_room *room, char flag)
{
	if (flag == FT_START)
	{
		if (li->start_room)
			return (FT_ONE_MORE_START);
		else
			li->start_room = room;
	}
	if 	(flag == FT_END)
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
			room->x = ft_room_atoi(line + i);
		else if (i > 1 && line[i - 1] == ' ' && space == 2)
			room->y = ft_room_atoi(line + i);
		i++;
	}
}

int			ft_create_room(char *line, t_lemin *li, char flag)
{
	t_room	*room;
	int		err;
	int		i;

	room = ft_room_new(li, &li->rooms);
	room->flags = flag;
	err = ft_found_flag(li, room, flag);
	i = -1;
	room->name = ft_strdup(line);
	while (line[++i] != ' ') //даб уже сделал это, поправь Андрей
		room->name[i] = line[i];
	room->name[i] = '\0';
	ft_coordinate_room(room, line, i);
	return (err);
}

int ft_search_hash(char *line, char *flag, int *err)
{
	if (*err == FT_NO_DATA)
		*err = FT_OK;
	if (line[0] == '#' && line[1] != '#')
		return (1);
	else if (!ft_strcmp(line, "##end"))
	{
		if (*flag != FT_NO_FLAGS)
			*err = FT_ONE_MORE_END;
		*flag = FT_END;
		return (1);
	}
	else if (!ft_strcmp(line, "##start"))
	{
		if (*flag != FT_NO_FLAGS)
			*err = FT_ONE_MORE_START;
		*flag = FT_START;
		return (1);
	}
	return (0);

}

int 	ft_scan_li(t_lemin *li)
{
	t_room	*ptr1;
	t_room	*ptr2;

	ptr1 = li->rooms;
	ptr2 = li->rooms;
	while (ptr1->next != NULL)
		ptr1 = ptr1->next;
	while (ptr2->next != NULL)
	{
		if (ptr1 == ptr2) //need? really?
			return(FT_DUP_ROOM);
		if (!ft_strcmp(ptr1->name, ptr2->name))
			return (FT_DUP_NAME);
		if (ptr1->x == ptr2->x && ptr1->y == ptr2->y)
			return(FT_DUP_COORDINATES);
		ptr2 = ptr2->next;
	}
	return (FT_OK);
}

int 	ft_parse_rooms(int fd, t_lemin *li, t_lstr *lstr, int err)
{
	char	*line;
	char	flag;

	flag = FT_NO_FLAGS;
	if (err == FT_OK)
		err = FT_NO_DATA;
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_strcmp(line, "\0"))
		{
			free(line);
			break ;
		}
		ft_string_insert(lstr, line, lstr->length);
		if ((err != FT_NO_DATA && err != FT_OK) || ft_search_hash(line, &flag, &err))
		{
			free(line);
			continue ;
		}
		if (err == FT_OK)
			err = ft_check_room(line, flag);
		if (err == FT_OK)
		{
			err = ft_create_room(line, li, flag);
			flag = FT_NO_FLAGS;
		}
		else if (err == FT_LINK)
			err = ft_parse_links(line, li, &flag);
		if (err == FT_OK)
			err = ft_scan_li(li);
		free(line);
	}
	return (err);
