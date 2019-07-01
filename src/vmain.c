
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 11:59:23 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/01 11:31:58 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_vis.h"

static int	ft_creation(t_lemin **li)
{
	if ((*li = (t_lemin*)ft_memalloc(sizeof(t_lemin))) == NULL)
		return (FT_MEMORY);
	if (((*li)->collisions =
				 (t_collision*)ft_memalloc(sizeof(t_collision))) == NULL)
		return (FT_MEMORY);
	return (FT_OK);
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

void	ft_move_ants(SDL_Renderer *ren, t_lemin *li, t_visualization *vis)
{
	static int step_num = 0;
	t_ant	*ant = vis->ants;

	while (ant)
	{
		if (step_num == 0 && ant->to != NULL)
		{
			ant->x = ant->from->x * vis->scale;
			ant->y = ant->from->y * vis->scale;
			ant->step_x = (ant->to->x - ant->from->x) / 50.0;
			ant->step_y = (ant->to->y - ant->from->y) / 50.0;
		}
		if (ant->to != NULL)
		{
			ant->x += ant->step_x * vis->scale; // можно складывать остатки
			ant->y += ant->step_y * vis->scale;
		}
		filledCircleColor(ren, ant->x + vis->offset_x, ant->y + vis->offset_y, (int)(0.1 * vis->scale), 0xFFFFFFFF);
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

void	ft_draw_lines(SDL_Renderer *ren, t_lemin *li, t_visualization *vis)
{
	t_room	*room;
	t_link	*link;

	room = li->rooms;
	while (room)
	{
		link = room->links;
		while (link)
		{
			thickLineRGBA (ren, room->x * vis->scale + vis->offset_x, room->y * vis->scale + vis->offset_y, link->room->x * vis->scale + vis->offset_x, link->room->y * vis->scale + vis->offset_y, (int)(vis->line_size * vis->scale), 102, 102, 102, 255);
			link = link->next;
		}
		room = room->next;
	}
}

void	ft_draw_rooms(SDL_Renderer *ren, t_lemin *li, t_visualization *vis)
{
	t_room *room;

	room = li->rooms;
	while (room)
	{
		if (room == li->start_room)
			filledCircleColor(ren, room->x * vis->scale + vis->offset_x, room->y * vis->scale + vis->offset_y, (int)(vis->room_size * vis->scale), 0xFF2EAF02);
		else if (room == li->end_room)
			filledCircleColor(ren, room->x * vis->scale + vis->offset_x, room->y * vis->scale + vis->offset_y, (int)(vis->room_size * vis->scale), 0xFF2E1AAF);
		else
		filledCircleColor(ren, room->x * vis->scale + vis->offset_x, room->y * vis->scale + vis->offset_y, (int)(vis->room_size * vis->scale), 0xFF2E1A6B);
		room = room->next;
	}
}

void	ft_move(t_visualization *vis)
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

void	ft_update_ants(t_visualization *vis, int old_scale, int new_scale)
{
	t_ant *ant_ptr;

	ant_ptr = vis->ants;
	while (ant_ptr)
	{
		ant_ptr->x =(int)((double)ant_ptr->x / old_scale * new_scale);
		ant_ptr->y = (int)((double)ant_ptr->y / old_scale * new_scale);
		ant_ptr = ant_ptr->next;
	}
}

void	ft_keyboard(t_visualization *vis, int *err)
{
	if (vis->e.type == SDL_QUIT || (vis->e.type == SDL_KEYDOWN && vis->e.key.keysym.sym == SDLK_ESCAPE))
		*err = 1;
	else if (vis->e.type == SDL_KEYDOWN)
	{
		if (vis->e.key.keysym.sym == SDLK_w || vis->e.key.keysym.sym == SDLK_UP)
			vis->move_keys |= FT_DIR_UP;
		else if (vis->e.key.keysym.sym == SDLK_s || vis->e.key.keysym.sym == SDLK_DOWN)
			vis->move_keys |= FT_DIR_DOWN;
		if (vis->e.key.keysym.sym == SDLK_a || vis->e.key.keysym.sym == SDLK_LEFT)
			vis->move_keys |= FT_DIR_LEFT;
		else if (vis->e.key.keysym.sym == SDLK_d || vis->e.key.keysym.sym == SDLK_RIGHT)
			vis->move_keys |= FT_DIR_RIGHT;
		if (vis->e.key.keysym.sym == SDLK_PLUS || vis->e.key.keysym.sym == SDLK_KP_PLUS)
		{
			ft_update_ants(vis, vis->scale, vis->scale + 5);
			vis->scale += 5;
		}
		else if (vis->e.key.keysym.sym == SDLK_MINUS || vis->e.key.keysym.sym == SDLK_KP_MINUS)
		{
			ft_update_ants(vis, vis->scale, vis->scale - 5);
			vis->scale -= 5;
		}
	}
	else if (vis->e.type == SDL_KEYUP)
	{
		if (vis->e.key.keysym.sym == SDLK_w || vis->e.key.keysym.sym == SDLK_UP)
			vis->move_keys &= !FT_DIR_UP;
		else if (vis->e.key.keysym.sym == SDLK_s || vis->e.key.keysym.sym == SDLK_DOWN)
			vis->move_keys &= !FT_DIR_DOWN;
		if (vis->e.key.keysym.sym == SDLK_a || vis->e.key.keysym.sym == SDLK_LEFT)
			vis->move_keys &= !FT_DIR_LEFT;
		else if (vis->e.key.keysym.sym == SDLK_d || vis->e.key.keysym.sym == SDLK_RIGHT)
			vis->move_keys &= !FT_DIR_RIGHT;
	}
}

int			ft_biggest_dif(int x_max, int x_min, int y_max, int y_min)
{
	int	size;
	if (x_max - x_min > y_max - y_min)
		size = 2200 / (x_max - x_min);
	else
		size = 1150 / (y_max - y_min);
	return (size);

}

int			ft_size_map(t_room *rooms)
{
	t_room *ptr;
	int y_max;
	int x_min;
	int x_max;
	int y_min;

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
	vis->room_size = 0.2;
	vis->line_size = 0.1;
}

int		main(void)
{
	t_visualization vis;
	int		err;
	t_lemin	*li;

	ft_bzero(&vis, sizeof(t_visualization));


	li = NULL;
	err = ft_creation(&li);
	if (err == FT_OK)
		err = ft_validation(0, li, ft_lstr_new_empty());
	if (err == FT_OK)
	{
		ft_search_scale(li, &vis);
		ft_read_step(li, &vis);
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
		vis.win = SDL_CreateWindow("ant", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2560, 1440, SDL_WINDOW_FULLSCREEN_DESKTOP);
		vis.ren = SDL_CreateRenderer(vis.win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		while (!err)
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
		SDL_DestroyRenderer(vis.ren);
		SDL_DestroyWindow(vis.win);
		SDL_Quit();
	}
	return (0);
}