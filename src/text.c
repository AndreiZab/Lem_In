#include "ft_vis.h"

void	ft_text_init(t_lemin *li, t_visualization *vis)
{
	TTF_Init();
	vis->str_ants = ft_itoa(li->ants);

	vis->rect.x = 15;
	vis->rect.y = 15;
	vis->rect.w = 200 + ft_strlen(vis->str_ants) * 40;
	vis->rect.h = 100;
	vis->font = TTF_OpenFont("/Library/Fonts/Courier New.ttf", 256);
	vis->color.a = 255;
	vis->color.b = 255;
	vis->color.g = 255;
	vis->color.r = 255;
}

void	ft_text_show(t_lemin	*li, t_visualization *vis)
{
	SDL_Surface	*surf;
	SDL_Texture	*texture;
	t_lstr	*lstr;
	char	*num;

	lstr = ft_lstr_new_copy("Ants: ");
	num = ft_itoa(li->ants_came);
	ft_lstr_insert_c(lstr, ' ', 5 - ft_strlen(num), lstr->length);
	ft_lstr_insert_s(lstr, num, lstr->length);
	ft_lstr_insert_c(lstr, '/', 1, lstr->length);
	ft_lstr_insert_s(lstr, vis->str_ants, lstr->length);
	surf = TTF_RenderText_Solid(vis->font, lstr->str, vis->color);
	free(num);
	ft_lstr_destroy(&lstr);
	texture = SDL_CreateTextureFromSurface(vis->ren, surf);
	SDL_RenderCopy(vis->ren, texture, NULL, &(vis->rect));
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surf);
}