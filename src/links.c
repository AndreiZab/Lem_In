#include "ft_lem_in.h"

static t_link	*ft_link_new(t_link **links)
{
	t_link	*link;
	t_link	*last;

	if (links == NULL)
		return (NULL);
	if ((link = (t_link*)ft_memalloc(sizeof(t_link))) == NULL)
		return (NULL);
	if (*links == NULL)
		*links = link;
	else
	{
		last = *links;
		while (last->next != NULL)
			last = last->next;
		last->next = link;
	}
	return (link);
}

void			ft_link_set(t_room *from, t_room *to)
{
	t_link	*link;

	link = ft_link_new(&from->output_links);
	link->linked_room = to;
	link->link_type = 0; //?
	link = ft_link_new(&to->input_links);
	link->linked_room = from;
	link->link_type = 0;
	++from->output_count;
	++to->input_count;
}

static void		ft_link_destroy(t_link **links, t_link *link, t_link *prev)
{
	if (prev == NULL)
		*links = link->next;
	else
		prev->next = link->next;
	free(link);
}

void			ft_link_unset_dir(t_room *from, t_room *to)
{
	t_link	*lnk;
	t_link	*prev;

	prev = NULL;
	lnk = to->input_links;
	while (lnk)
	{
		if (lnk->linked_room == from)
		{
			ft_link_destroy(&to->input_links, lnk, prev);
			--to->input_count;
			break ;
		}
		prev = lnk;
		lnk = lnk->next;
	}
	prev = NULL;
	lnk = from->output_links;
	while (lnk)
	{
		if (lnk->linked_room == to)
		{
			ft_link_destroy(&from->output_links, lnk, prev);
			--from->output_count;
			break ;
		}
		prev = lnk;
		lnk = lnk->next;
	}
}