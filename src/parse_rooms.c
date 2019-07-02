/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:59:40 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/02 17:47:59 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_lem_in.h"
#define FT_LINK 99

int		ft_room_atoi(const char *str)
{
	int		i;
	long	numb;
	char	s;

	i = 0;
	while (('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ')
		++i;
	s = 1;
	if (str[i] == '-')
		s = -1;
	if (str[i] == '+' || str[i] == '-')
		++i;
	numb = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		numb = numb * 10 + (str[i++] - '0');
		if (numb < 0)
			return (0);
	}
	if ((numb > 2147483648 && s == -1) || (numb > 2147483647 && s == 1))
		return (0);
	return ((int)numb * s);
}

int		ft_err_manager(char *line, int *i, int *space)
{
	if ((line[*i] > 57 || line[*i] < 48) && line[*i] != 45)
		return (FT_WRONG_FORMAT);
	if (*i > 1 && line[*i - 1] == ' ' && ++(*space))
		if (ft_room_atoi(line + *i) == 0 && line[*i] != '0')
			return (FT_WRONG_FORMAT);
	return (FT_OK);
}

int		ft_check_room(char *line, char flag)
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
		if (line[i] == '-' && i > 1 && line[i - 1] != ' ')
			return (FT_LINK);
		if (ft_err_manager(line, &i, &space))
			return (FT_WRONG_FORMAT);
		i++;
	}
	if (space != 2 || flag == FT_ERROR)
		return (FT_WRONG_FORMAT);
	return (FT_OK);
}

int		ft_hash(char *line, char *flag, int *err)
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

int		ft_parse_rooms(int fd, t_lemin *li, t_lstr *lstr, int err)
{
	char *line;
	char flag;

	line = NULL;
	flag = FT_NO_FLAGS;
	while (ft_free_line(line) && get_next_line(fd, &line) > 0)
	{
		if (!ft_strcmp(line, "\0") && ft_free_line(line))
			break ;
		ft_string_insert(lstr, line, lstr->length);
		if ((err != FT_NO_DATA && err != FT_OK) || ft_hash(line, &flag, &err))
			continue ;
		if (err == FT_OK)
			err = ft_check_room(line, flag);
		if (err == FT_OK)
			err = ft_create_room(line, li, &flag);
		else if (err == FT_LINK)
			err = ft_parse_links(line, li, &flag);
		if (err == FT_OK)
			err = ft_scan_li(li);
	}
	return (err);
}
