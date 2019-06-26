/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:46:04 by rhealitt          #+#    #+#             */
/*   Updated: 2019/06/25 13:58:34 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

unsigned int		ft_ant_atoi(const char *str)
{
	int		i;
	long	numb;

	i = 0;
	while (('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ')
		++i;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		++i;
	numb = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		numb = numb * 10 + (str[i++] - '0');
		if (numb < 0 || numb > 4294967295)
			return (0);
	}
	return ((unsigned int)numb);
}

int 	ft_parse_ants(int fd, t_lemin *li, t_lstr *lstr)
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
	while(line[i] != '\0')
	{
		if (line[i] == '-')
			err = FT_NO_ANTS;
		if (i == 0 && line[i] == '+')
			i++;
		if (line[i] > 57 || line[i] < 48)
			err = FT_WRONG_FORMAT;
		i++;
	}
	li->ants = ft_ant_atoi(line);
	if (li->ants <= 0)
		err = FT_NO_ANTS;
	free (line);
	return (err);

int		ft_validation(int fd, t_lemin *li, t_lstr *lstr)
{
	int err;

	err = ft_parse_ants(fd, li, lstr);
	if (err == FT_OK)
		err = ft_parse_rooms(fd, li, lstr);
/*  ->  ft_parse_links(fd, li, lstr); уехал в парс комнат */
	return (err);
}
