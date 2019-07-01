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



typedef struct	s_visualization
{
	int		scale;
	double 	room_size;
	double 	line_size;
	int		offset_x;
	int		offset_y;
	char 	move_keys;
	SDL_Event	e;
	SDL_Window	*win;
	SDL_Renderer	*ren;
	struct s_ant *ants;
}				t_visualization;

typedef struct	s_ant
{
	int		number;
	t_room	*from;
	t_room	*to;
	double	step_x;
	double	step_y;
	int		x;
	int		y;
	struct s_ant *next;
}				t_ant;

void	ft_read_step(t_lemin *li, t_visualization *vis);

#endif
