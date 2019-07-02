/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 12:50:17 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/02 12:50:17 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_vis.h"

static void	ft_move(t_visualization *vis)
{
	if (vis->move_keys & FT_DIR_UP)
		vis->offset_y -= 5;
	if (vis->move_keys & FT_DIR_DOWN)
		vis->offset_y += 5;
	if (vis->move_keys & FT_DIR_RIGHT)
		vis->offset_x += 5;
	if (vis->move_keys & FT_DIR_LEFT)
		vis->offset_x -= 5;
}

static int	ft_biggest_dif(int x_max, int x_min, int y_max, int y_min)
{
	int size;

	if (x_max - x_min > y_max - y_min)
		size = 2200 / (x_max - x_min);
	else
		size = 1150 / (y_max - y_min);
	return (size);
}

static int	ft_size_map(t_room *rooms)
{
	t_room	*ptr;
	int		y_max;
	int		x_min;
	int		x_max;
	int		y_min;

	ptr = rooms;
	y_max = ptr->y;
	x_min = ptr->x;
	x_max = ptr->x;
	y_min = ptr->y;
	while (ptr)
	{
		if (++ptr->x > x_max)
			x_max = ptr->x;
		if (ptr->x < x_min)
			x_min = ptr->x;
		if (++ptr->y > y_max)
			y_max = ptr->y;
		if (ptr->y++ < y_min)
			y_min = ptr->y;
		ptr = ptr->next;
	}
	return (ft_biggest_dif(x_max, x_min, y_max, y_min));
}

void		ft_search_scale(t_lemin *li, t_visualization *vis)
{
	vis->scale = ft_size_map(li->rooms);
	vis->room_size = 0.2 / vis->scale * 100;
	vis->line_size = 0.1 / vis->scale * 100;
}

void		ft_main_draw(t_lemin *li, t_visualization vis, int err)
{
	while (err < 1)
	{
		while (SDL_PollEvent(&vis.e))
			ft_keyboard(&vis, &err);
		ft_move(&vis);
		SDL_SetRenderDrawColor(vis.ren, 0, 0, 0, 0);
		SDL_RenderClear(vis.ren);
		ft_draw_lines(vis.ren, li, &vis);
		ft_draw_rooms(vis.ren, li, &vis);
		ft_move_ants(vis.ren, li, &vis);
		SDL_RenderPresent(vis.ren);
	}
}
