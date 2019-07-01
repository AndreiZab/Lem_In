#include "../include/ft_vis.h"

static	ft_ant_state(t_visualization *vis, int ant_n, t_ant **finded)
{
	t_ant	*ant;

	ant = vis->ants;
	while (ant)
	{
		if (ant->number == ant_n)
		{
			*finded = ant;
			return (ant->to == NULL) ? FT_ANT_AT_END : FT_ANT_ON_PATH;
		}
		ant = ant->next;
	}
	*finded = NULL; //or create new
	return (FT_ANT_NOT_SPAWNED);
}

int		ft_set_ant_movement(t_lemin *li, t_visualization *vis, char *str_move)
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
		return (FT_NOT_A_STEP);
	ant_number = ft_atoi(splited[0]);
	if ((room = ft_room_by_name(li->rooms, splited[1])) == NULL)
		return (FT_NOT_A_STEP);
	ant = NULL;
	ant_state = ft_ant_state(vis, ant_number, &ant);
	if (ant_state == FT_ANT_NOT_SPAWNED)
		ant->from = li->start_room;
	else if (ant_state == FT_ANT_ON_PATH)
		ant->from = ant->to;
	ant->to = room;
		
}

void	ft_read_step(t_lemin *li, t_visualization *vis)
{
	char	*line;
	char	**splited;
	int		i;

	line = NULL;
	if (get_next_line(0, &line) > 0)
	{
		splited = ft_strsplit(line, ' ');
		i = 0;
		while (splited[i] != NULL)
			ft_set_ant_movement(vis, splited[i++]);
	}
}