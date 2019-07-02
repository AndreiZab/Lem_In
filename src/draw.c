/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 12:38:16 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/02 12:48:15 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_vis.h"

void		ft_draw_lines(SDL_Renderer *ren, t_lemin *li, t_visualization *vis)
{
	t_room	*room;
	t_link	*link;

	room = li->rooms;
	while (room)
	{
		link = room->links;
		while (link)
		{
			thickLineRGBA(ren, room->x * vis->scale + vis->offset_x, room->y
			* vis->scale + vis->offset_y, link->room->x * vis->scale +
			vis->offset_x, link->room->y * vis->scale + vis->offset_y,
			(int)(vis->line_size * vis->scale), 102, 102, 102, 255);
			link = link->next;
		}
		room = room->next;
	}
}

void		ft_draw_rooms(SDL_Renderer *ren, t_lemin *li, t_visualization *vis)
{
	t_room *room;

	room = li->rooms;
	while (room)
	{
		if (room == li->start_room)
			filledCircleColor(ren, room->x * vis->scale + vis->offset_x,
					room->y * vis->scale + vis->offset_y,
					(int)(vis->room_size * vis->scale), 0xFF2EAF02);
		else if (room == li->end_room)
			filledCircleColor(ren, room->x * vis->scale + vis->offset_x,
					room->y * vis->scale + vis->offset_y,
					(int)(vis->room_size * vis->scale), 0xFF2E1AAF);
		else
			filledCircleColor(ren, room->x * vis->scale + vis->offset_x,
					room->y * vis->scale + vis->offset_y,
					(int)(vis->room_size * vis->scale), 0xFF2E1A6B);
		room = room->next;
	}
}

static void	ft_stop_ants(t_visualization *vis)
{
	t_ant	*ant;

	ant = vis->ants;
	while (ant)
	{
		if (ant->to)
		{
			ant->from = ant->to;
			ant->to = NULL;
		}
		ant = ant->next;
	}
}

static void	ft_step_newroom(t_ant *ant, t_visualization *vis)
{
	ant->x = ant->from->x * vis->scale * 1000;
	ant->y = ant->from->y * vis->scale * 1000;
	ant->step_x = (ant->to->x - ant->from->x) / 50.0;
	ant->step_y = (ant->to->y - ant->from->y) / 50.0;
}

void		ft_move_ants(SDL_Renderer *ren, t_lemin *li, t_visualization *vis)
{
	static int	step_num = 0;
	t_ant		*ant;

	ant = vis->ants;
	while (ant)
	{
		if (step_num == 0 && ant->to != NULL)
			ft_step_newroom(ant, vis);
		if (ant->to != NULL)
		{
			ant->x += ant->step_x * vis->scale * 1000;
			ant->y += ant->step_y * vis->scale * 1000;
		}
		filledCircleColor(ren, ant->x / 1000 + vis->offset_x, ant->y / 1000 +
		vis->offset_y, (int)(0.09 / vis->scale * 100 * vis->scale), 0xFFFFFFFF);
		ant = ant->next;
	}
	step_num++;
	if (step_num == 50)
	{
		ft_stop_ants(vis);
		ft_read_step(li, vis);
		step_num = 0;
	}
}
