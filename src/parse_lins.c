/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:30:22 by rhealitt          #+#    #+#             */
/*   Updated: 2019/06/23 18:27:28 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

int		ft_split_link(char *line, char **name1, char **name2)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '-')
		{
			*name1 = ft_strdup(line); // поправить лишний перебор
			(*name1)[i] = '\0';
			*name2 = ft_strdup(line + i + 1);
			if (*name1 == *name2)
				return (FT_WRONG_FORMAT);
			if (*name1 && *name2 && *name1[0] != '\0' && *name2[0] != '\0')
				return (FT_OK);
		}
		i++;
	}
	return (FT_WRONG_FORMAT);
}

int		ft_parse_links(char *line, t_lemin *li)
{
	int		status;
	char	*name1;
	char	*name2;
	t_room	*ptr1;
	t_room	*ptr2;

	ptr1 = NULL;
	ptr2 = NULL;
	status = ft_split_link(line, &name1, &name2);
	if (!li->rooms)
		return (FT_NO_ROOMS); //разве так?
	while (li->rooms)
	{
		if (!ft_strcmp(li->rooms->name, name2))
			ptr2 = li->rooms;
		if (!ft_strcmp(li->rooms->name, name1))
			ptr1 = li->rooms;
		if ((ptr1 && ptr2) || !li->rooms->next)
			break;
		li->rooms = li->rooms->next;
	}
	if (!ptr1 || !ptr2)
		return (FT_WRONG_FORMAT);
	ft_link_set(ptr1, ptr2);
	ft_link_set(ptr2, ptr1);
	return (status);
}

/*
 рум-линк-рум не забыть поправить
 обработать дефисы в найме
 */
