#include "ft_lem_in.h"

int			ft_solution(t_lemin *li)
{
	int		err;

	if ((err = ft_bfs(li)) != FT_OK)
		return (err);
	
}