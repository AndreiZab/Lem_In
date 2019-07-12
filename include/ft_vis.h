/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vis.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 12:57:25 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/12 11:55:51 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VIS_H
# define FT_VIS_H
# define FT_DIR_LEFT (1)
# define FT_DIR_RIGHT (1 << 1)
# define FT_DIR_UP (1 << 2)
# define FT_DIR_DOWN (1 << 3)
# define FT_ANT_NOT_SPAWNED 0
# define FT_ANT_ON_PATH 1
# define FT_ANT_AT_END 2
# include "ft_lem_in.h"
# include <SDL.h>
# include <SDL2_gfxPrimitives.h>
# include <SDL_ttf.h>

typedef struct		s_visualization
{
	int				scale;
	double			room_size;
	double			line_size;
	int				offset_x;
	int				offset_y;
	char			move_keys;
	SDL_Event		e;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	struct s_ant	*ants;
	TTF_Font		*font;
	SDL_Rect		rect;
	SDL_Color		color;
	char			*str_ants;
}					t_visualization;

typedef struct		s_ant
{
	int				number;
	t_room			*from;
	t_room			*to;
	double			step_x;
	double			step_y;
	int				x;
	int				y;
	struct s_ant	*next;
}					t_ant;

/*
** step_reader.c
*/

void				ft_read_step(t_lemin *li, t_visualization *vis);

/*
** draw.c
*/

void				ft_draw_lines(SDL_Renderer *ren, t_lemin *li,
								  t_visualization *vis);
void				ft_draw_rooms(SDL_Renderer *ren, t_lemin *li,
		t_visualization *vis);
void				ft_move_ants(SDL_Renderer *ren, t_lemin *li,
		t_visualization *vis);

/*
** visualization_tools.c
*/

void				ft_main_draw(t_lemin *li, t_visualization *vis, int err);

/*
** vmain.c
*/

void				ft_keyboard(t_visualization *vis, int *err);

/*
** lem_in.c
*/

int					ft_free(t_lemin **li, t_lstr **lstr);

/*
** text.c
*/

void				ft_text_init(t_lemin *li, t_visualization *vis);
void				ft_text_show(t_lemin	*li, t_visualization *vis);

#endif
