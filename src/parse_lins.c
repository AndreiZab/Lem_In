/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhealitt <rhealitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 20:30:22 by rhealitt          #+#    #+#             */
/*   Updated: 2019/06/27 15:54:53 by rhealitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_lem_in.h"

void		ft_string_insert(t_lstr *lstr, char *str, int index)
{
	int	len;

	if (lstr == NULL || str == NULL || index < 0 || index > lstr->length)
		return ;
	len = (int)ft_strlen(str);
	str[len] = '\n';
	len += 1;
	if (lstr->capacity < lstr->length + 1 + len)
		if (!ft_lstr_resize(lstr, lstr->length + len))
			return ;
	if (index != lstr->length)
		ft_memmove(lstr->str + index + len, lstr->str + index,
				lstr->length - index);
	ft_memcpy(lstr->str + index, str, len);
	lstr->length += len;
	lstr->str[lstr->length] = 0;
	str[len - 1] = '\0';
}

int			ft_free(char *line)
{
	free(line);
	return (1);
}

int			ft_scan_li(t_lemin *li)
{
	t_room	*ptr1;
	t_room	*ptr2;

	ptr1 = li->rooms;
	ptr2 = li->rooms;
	while (ptr1->next != NULL)
		ptr1 = ptr1->next;
	while (ptr2->next != NULL)
	{
		if (ptr1 == ptr2)
			return (FT_DUP_ROOM);
		if (!ft_strcmp(ptr1->name, ptr2->name))
			return (FT_DUP_NAME);
		if (ptr1->x == ptr2->x && ptr1->y == ptr2->y)
			return (FT_DUP_COORDINATES);
		ptr2 = ptr2->next;
	}
	return (FT_OK);
}

static int	ft_parse_linkname(t_lemin *li, char *name1, char *name2)
{
	t_room	*ptr1;
	t_room	*ptr2;
	t_room	*ptr3;

	ptr1 = NULL;
	ptr2 = NULL;
	ptr3 = li->rooms;
	while (ptr3)
	{
		if (!ft_strcmp(ptr3->name, name2))
			ptr2 = ptr3;
		if (!ft_strcmp(ptr3->name, name1))
			ptr1 = ptr3;
		if ((ptr1 && ptr2) || !ptr3->next)
			break ;
		ptr3 = ptr3->next;
	}
	if (!ptr1 || !ptr2 || ptr1 == ptr2 || ft_search_dup_link(ptr1, ptr2))
		return (FT_DUP_NAME);
	ft_link_set(ptr1, ptr2);
	ft_link_set(ptr2, ptr1);
	return (FT_OK);
}

int			ft_parse_links(char *line, t_lemin *li, char *flag)
{
	int		err;
	char	*name1;
	char	*name2;

	*flag = FT_ERROR;
	if (!li->rooms)
		return (FT_NO_ROOMS);
	if (!li->end_room)
		return (FT_NO_END);
	if (!li->start_room)
		return (FT_NO_START);
	err = ft_split_link(line, &name1, &name2);
	if (err == FT_OK)
		err = ft_parse_linkname(li, name1, name2);
	free(name2);
	free(name1);
	return (err);
}
