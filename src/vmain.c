/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 11:59:23 by rhealitt          #+#    #+#             */
/*   Updated: 2019/06/30 15:59:09 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_lem_in.h"
#include <SDL2_gfxPrimitives.h>
#include <SDL.h>

static int	ft_creation(t_lemin **li)
{
	if ((*li = (t_lemin*)ft_memalloc(sizeof(t_lemin))) == NULL)
		return (FT_MEMORY);
	if (((*li)->collisions =
				 (t_collision*)ft_memalloc(sizeof(t_collision))) == NULL)
		return (FT_MEMORY);
	return (FT_OK);
}

void	ft_move_ants(SDL_Renderer *ren, t_lemin *li, t_visualization *vis)
{
	static int step_num = 0;
	t_ant	*ant = vis->ants;

	if (step_num == 0 && ant->to != NULL) {
		ant->x = ant->from->x * vis->scale;
		ant->y = ant->from->y * vis->scale;
		ant->step_x = (ant->to->x - ant->from->x) / 50.0;
		ant->step_y = (ant->to->y - ant->from->y) / 50.0;
	}
	if (ant->to != NULL) {
		ant->x += ant->step_x * vis->scale;
		ant->y += ant->step_y * vis->scale;
	}
	filledCircleColor(ren, ant->x + vis->offset_x, ant->y + vis->offset_y, (int)(0.1 * vis->scale), 0xFFFFFFFF);

	step_num++;
	if (step_num == 50)
	{
		if (ant->to)
		{
			ant->from = ant->to;
			ant->to = ant->to->next;
		}

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
			thickLineRGBA (ren, room->x * vis->scale + vis->offset_x, room->y * vis->scale + vis->offset_y, link->room->x * vis->scale + vis->offset_x, link->room->y * vis->scale + vis->offset_y, (int)(vis->line_size * vis->scale), 0, 0, 0, 255);
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
		filledCircleColor(ren, room->x * vis->scale + vis->offset_x, room->y * vis->scale + vis->offset_y, (int)(vis->room_size * vis->scale), 0xFFFF0000);
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
		if (vis->e.key.keysym.sym == SDLK_PLUS || vis->e.key.keysym.sym == SDLK_KP_PLUS) {
			ft_update_ants(vis, vis->scale, vis->scale + 5);
			vis->scale += 5;
		}
		else if (vis->e.key.keysym.sym == SDLK_MINUS || vis->e.key.keysym.sym == SDLK_KP_MINUS) {
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

int		main(void)
{
	t_visualization vis;
	int		err;
	t_lemin	*li;

	ft_bzero(&vis, sizeof(t_visualization));

	vis.scale = 50;
	vis.room_size = 0.3;
	vis.line_size = 0.1;
	li = NULL;
	err = ft_creation(&li);
	if (err == FT_OK)
		err = ft_validation(0, li, ft_lstr_new_empty());
	vis.ants = ft_memalloc(sizeof(t_ant));
	vis.ants->to = li->rooms->next;
	vis.ants->from = li->rooms;
	if (err == FT_OK) {
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
		vis.win = SDL_CreateWindow("ant", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2560, 1440, SDL_WINDOW_FULLSCREEN_DESKTOP);
		vis.ren = SDL_CreateRenderer(vis.win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		while (!err)
		{
			while (SDL_PollEvent(&vis.e))
				ft_keyboard(&vis, &err);
			ft_move(&vis);
			SDL_SetRenderDrawColor(vis.ren, 0, 255, 0, 255);
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

}