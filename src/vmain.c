/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 11:59:23 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/02 17:14:32 by rhealitt         ###   ########.fr       */
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

static void	ft_update_ants(t_visualization *vis, int old_scale, int new_scale)
{
	t_ant *ant_ptr;

	ant_ptr = vis->ants;
	while (ant_ptr)
	{
		ant_ptr->x = (int)((double)ant_ptr->x / old_scale * new_scale);
		ant_ptr->y = (int)((double)ant_ptr->y / old_scale * new_scale);
		ant_ptr = ant_ptr->next;
	}
}

static void	ft_sdl_keydown(t_visualization *vis)
{
	if (vis->e.key.keysym.sym == SDLK_w || vis->e.key.keysym.sym == SDLK_UP)
		vis->move_keys |= FT_DIR_UP;
	else if (vis->e.key.keysym.sym == SDLK_s ||
	vis->e.key.keysym.sym == SDLK_DOWN)
		vis->move_keys |= FT_DIR_DOWN;
	if (vis->e.key.keysym.sym == SDLK_a || vis->e.key.keysym.sym == SDLK_LEFT)
		vis->move_keys |= FT_DIR_LEFT;
	else if (vis->e.key.keysym.sym == SDLK_d ||
	vis->e.key.keysym.sym == SDLK_RIGHT)
		vis->move_keys |= FT_DIR_RIGHT;
	if (vis->e.key.keysym.sym == SDLK_PLUS ||
	vis->e.key.keysym.sym == SDLK_KP_PLUS)
	{
		ft_update_ants(vis, vis->scale, vis->scale + 5);
		vis->scale += 5;
	}
	else if (vis->e.key.keysym.sym == SDLK_MINUS ||
	vis->e.key.keysym.sym == SDLK_KP_MINUS)
	{
		ft_update_ants(vis, vis->scale, vis->scale - 5);
		vis->scale -= 5;
	}
}

void		ft_keyboard(t_visualization *vis, int *err)
{
	if (vis->e.type == SDL_QUIT || (vis->e.type == SDL_KEYDOWN &&
	vis->e.key.keysym.sym == SDLK_ESCAPE))
		*err = 1;
	else if (vis->e.type == SDL_KEYDOWN)
	{
		ft_sdl_keydown(vis);
	}
	else if (vis->e.type == SDL_KEYUP)
	{
		if (vis->e.key.keysym.sym == SDLK_w || vis->e.key.keysym.sym == SDLK_UP)
			vis->move_keys &= !FT_DIR_UP;
		else if (vis->e.key.keysym.sym == SDLK_s ||
		vis->e.key.keysym.sym == SDLK_DOWN)
			vis->move_keys &= !FT_DIR_DOWN;
		if (vis->e.key.keysym.sym == SDLK_a ||
		vis->e.key.keysym.sym == SDLK_LEFT)
			vis->move_keys &= !FT_DIR_LEFT;
		else if (vis->e.key.keysym.sym == SDLK_d ||
		vis->e.key.keysym.sym == SDLK_RIGHT)
			vis->move_keys &= !FT_DIR_RIGHT;
	}
}

int			main(void)
{
	t_visualization	vis;
	int				err;
	t_lemin			*li;
	t_lstr			*lstr;

	lstr = ft_lstr_new_empty();
	ft_bzero(&vis, sizeof(t_visualization));
	li = NULL;
	err = ft_creation(&li);
	if (err == FT_OK)
		err = ft_validation(0, li, lstr);
	if (err < 1)
	{
		ft_read_step(li, &vis);
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
		vis.win = SDL_CreateWindow("ant_window", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, 2560, 1440,
				SDL_WINDOW_FULLSCREEN_DESKTOP);
		vis.ren = SDL_CreateRenderer(vis.win, -1, SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC);
		ft_main_draw(li, &vis, err);
		SDL_DestroyRenderer(vis.ren);
		SDL_DestroyWindow(vis.win);
		SDL_Quit();
	}
	ft_free(&li, &lstr);
	exit(0);
}
