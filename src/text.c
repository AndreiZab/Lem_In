/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:57:05 by rhealitt          #+#    #+#             */
/*   Updated: 2019/07/02 19:18:51 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_vis.h"

void	ft_text_init(t_lemin *li, t_visualization *vis)
{
	TTF_Init();
	vis->str_ants = ft_itoa(li->ants);
	vis->rect.x = 15;
	vis->rect.y = 15;
	vis->rect.w = 200 + ft_strlen(vis->str_ants) * 40;
	vis->rect.h = 50;
	vis->font = TTF_OpenFont("/include/arnamu_mono.ttf", 256);
	vis->color.a = 255;
	vis->color.b = 255;
	vis->color.g = 255;
	vis->color.r = 255;
}

void	ft_free(t_lemin **li)
{
	t_path		*path;
	t_path		*path_next;
	t_collision	*collision;

	if (li && *li)
	{
		path = (*li)->paths;
		while (path)
		{
			path_next = path->next;
			free(path);
			path = path_next;
		}
		collision = (*li)->collisions;
		while (collision->prev)
		{
			collision = collision->prev;
			free(collision->next);
		}
		free(collision);
		ft_room_full_free(&(*li)->rooms);
		free(*li);
		*li = NULL;
	}
}

void	ft_text_show(t_lemin *li, t_visualization *vis)
{
	SDL_Surface	*surf;
	SDL_Texture	*texture;
	t_lstr		*lstr;
	char		*num;

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
