/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:52:15 by rhealitt          #+#    #+#             */
/*   Updated: 2019/06/21 20:52:19 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static int	ft_creation(t_lemin **li, t_lstr **lstr)
{
	if ((*li = (t_lemin*)ft_memalloc(sizeof(t_lemin))) == NULL)
		return (FT_MEMORY);
	if (((*li)->collisions = (t_collision*)ft_memalloc(sizeof(t_collision))) == NULL)
		return (FT_MEMORY);
	if ((*lstr = ft_lstr_new_empty()) == NULL)
		return (FT_MEMORY);
	return (FT_OK);
}

static void	ft_output(int error_state, t_lstr *lstr)
{
	if (error_state == FT_OK)
		ft_lstr_put(lstr);
	else
		ft_putstr("ERROR\n");
}

static void	ft_free(t_lemin **li, t_lstr **lstr)
{
	if (li && *li)
	{
		ft_room_full_free(&(*li)->rooms);
		/*ft_path_full_free((*li)->paths);*/
		free(*li);
		*li = NULL;
	}
	lstr ? ft_lstr_destroy(lstr) : NULL;
}


//удалить в релизе
static int	ft_test_input(t_lemin *li, t_lstr *lstr)
{
	t_room *room;
	t_room *rm;

	ft_lstr_insert_s(lstr, "5\n##start\n0 1 2\n1 5 4\n##end\n2 8 5\n0-1\n1-2\n\n", 0);
	li->ants = 5;

	room = ft_room_new(li, &li->rooms);
	room->name = ft_strnew(1);
	room->name[0] = '0';
	room->x = 1;
	room->y = 2;
	li->start_room = room;

	room = ft_room_new(li, &li->rooms);
	room->name = ft_strnew(1);
	room->name[0] = '1';
	room->x = 5;
	room->y = 4;

	room = ft_room_new(li, &li->rooms);
	room->name = ft_strnew(1);
	room->name[0] = '2';
	room->x = 8;
	room->y = 5;
	li->end_room = room;

	rm = ft_room_new(li, &li->rooms);
	rm->name = ft_strnew(1);
	rm->name[0] = '3';
	rm->x = 8;
	rm->y = 5;

	
	ft_link_set(li->rooms, li->rooms->next);
	ft_link_set(li->rooms->next, li->rooms->next->next);
	ft_link_set(li->rooms, rm);
	ft_link_set(rm, li->rooms->next->next);
	return (FT_OK);
}

int			main(void)
{
	int		err;
	t_lemin	*li;
	t_lstr	*lstr;

	li = NULL;
	lstr = NULL;
	err = ft_creation(&li, &lstr);
	if (err == FT_OK)
		//err = ft_test_input(li, lstr);
		err = ft_validation(0, li, lstr);
	if (err == FT_OK)
		err = ft_solution(li);
	if (err != FT_OK)
		ft_putnbr(err);
	if (err == FT_OK)
	 	err = ft_migration(li, lstr);
	ft_output(err, lstr);
	ft_free(&li, &lstr);
	return (0);
}