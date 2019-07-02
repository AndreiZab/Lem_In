#include "ft_vis.h"

void	text_init(t_lemin *li, t_visualization *vis)
{
	TTF_Init();
	vis->str_ants = ft_itoa(li->ants);
	vis->rect.x = 15;
	vis->rect.y = 15;
	vis->rect.w = 200;
	vis->rect.h = 100;
	vis->font = TTF_OpenFont("/Library/Fonts/Arial.ttf");
	vis->color.a = 255;
	vis->color.b = 255;
	vis->color.g = 255;
	vis->color.r = 255;
}