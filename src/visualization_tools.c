/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 12:50:17 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/03 12:04:38 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_vis.h"

static void	ft_move(t_visualization *vis)
{
	if (vis->move_keys & FT_DIR_UP)
		vis->offset_y += 5;
	if (vis->move_keys & FT_DIR_DOWN)
		vis->offset_y -= 5;
	if (vis->move_keys & FT_DIR_RIGHT)
		vis->offset_x -= 5;
	if (vis->move_keys & FT_DIR_LEFT)
		vis->offset_x += 5;
}

static void	ft_size_map(int *coor, t_visualization *vis)
{
	if ((coor[0] - coor[1]) > (coor[2] - coor[3]))
	{
		if ((coor[0] - coor[1]) > (coor[2] - coor[3]) * 1.78)
			vis->scale = 2091 / (coor[0] - coor[1]);
		else
			vis->scale = 1224 / (coor[2] - coor[3]);
	}
	else
	{
		vis->scale = 1224 / (coor[2] - coor[3]);
	}
	vis->room_size = 0.2 / vis->scale * 100;
	vis->line_size = 0.1 / vis->scale * 100;
}

/*
**	coor[0] x_max
**	coor[1] x_min
**	coor[2] y_max
**	coor[3] y_min
*/

static int	*ft_search_scale(t_lemin *li, t_visualization *vis)
{
	t_room	*ptr;
	int		*coor;

	coor = (int*)ft_memalloc(sizeof(int) * 4);
	ptr = li->rooms;
	coor[0] = ptr->x;
	coor[1] = ptr->x;
	coor[2] = ptr->y;
	coor[3] = ptr->y;
	while (ptr)
	{
		if (ptr->x > coor[0])
			coor[0] = ptr->x;
		if (ptr->x < coor[1])
			coor[1] = ptr->x;
		if (ptr->y > coor[2])
			coor[2] = ptr->y;
		if (ptr->y < coor[3])
			coor[3] = ptr->y;
		ptr = ptr->next;
	}
	ft_size_map(coor, vis);
	return (coor);
}

static void	ft_centering(t_lemin *li, t_visualization *vis)
{
	int *coor_ptr;

	coor_ptr = ft_search_scale(li, vis);
	vis->offset_x = (int)(-coor_ptr[1] * vis->scale + (vis->scale / 2));
	vis->offset_y = (int)(-coor_ptr[3] * vis->scale + (vis->scale / 2));
	free(coor_ptr);
}

void		ft_main_draw(t_lemin *li, t_visualization *vis, int err)
{
	ft_text_init(li, vis);
	ft_centering(li, vis);
	while (err < 1)
	{
		while (SDL_PollEvent(&(vis->e)))
			ft_keyboard(vis, &err);
		ft_move(vis);
		SDL_SetRenderDrawColor(vis->ren, 0, 0, 0, 0);
		SDL_RenderClear(vis->ren);
		ft_draw_lines(vis->ren, li, vis);
		ft_draw_rooms(vis->ren, li, vis);
		ft_move_ants(vis->ren, li, vis);
		ft_text_show(li, vis);
		SDL_RenderPresent(vis->ren);
	}
	free(vis->str_ants);
	TTF_CloseFont(vis->font);
	TTF_Quit();
}
