/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:20:00 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/03 13:02:30 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_vis.h"

static int	ft_ant_state(t_lemin *li, t_visualization *vis,
		int ant_n, t_ant **finded)
{
	t_ant	*ant;
	t_ant	*prev;

	ant = vis->ants;
	while (ant)
	{
		if (ant->number == ant_n)
		{
			*finded = ant;
			return (FT_ANT_ON_PATH);
		}
		prev = ant;
		ant = ant->next;
	}
	*finded = (t_ant*)ft_memalloc(sizeof(t_ant));
	(*finded)->number = ant_n;
	(*finded)->from = li->start_room;
	if (vis->ants == NULL)
		vis->ants = *finded;
	else
		prev->next = *finded;
	return (FT_ANT_NOT_SPAWNED);
}

int			ft_splited_free(char **splited, int state)
{
	int		i;

	i = -1;
	while (splited[++i])
		free(splited[i]);
	free(splited);
	return (state);
}

int			ft_set_ant_movement(t_lemin *li,
		t_visualization *vis, char *str_move)
{
	char	**splited;
	int		ant_number;
	t_room	*room;
	t_ant	*ant;
	int		ant_state;

	if (*str_move != 'L')
		return (FT_NOT_A_STEP);
	splited = ft_strsplit(str_move + 1, '-');
	if (splited[2] != NULL || !ft_isint(splited[0]))
		return (ft_splited_free(splited, FT_NOT_A_STEP));
	ant_number = ft_atoi(splited[0]);
	if ((room = ft_room_by_name(li->rooms, splited[1])) == NULL)
		return (ft_splited_free(splited, FT_NOT_A_STEP));
	ant = NULL;
	ant_state = ft_ant_state(li, vis, ant_number, &ant);
	ant->to = room;
	return (ft_splited_free(splited, FT_OK));
}

void		ft_read_step(t_lemin *li, t_visualization *vis)
{
	char	*line;
	char	**splited;
	int		i;

	line = NULL;
	if (get_next_line(0, &line) > 0)
	{
		if (!line)
			return ;
		splited = ft_strsplit(line, ' ');
		i = 0;
		while (splited[i] != NULL)
			ft_set_ant_movement(li, vis, splited[i++]);
		free(line);
		ft_splited_free(splited, 0);
	}
}
