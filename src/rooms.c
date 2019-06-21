#include "ft_lem_in.h"

/*
** Create new room in room's array and return it
** Room index will set automatically
*/

t_room	*ft_room_new(t_room **rooms)
{
	t_room	*room;
	t_room	*last;

	if (rooms == NULL)
		return (NULL);
	if ((room = (t_room*)ft_memalloc(sizeof(t_room))) == NULL)
		return (NULL);
	if (*rooms == NULL)
		*rooms = room;
	else
	{
		last = *rooms;
		while (last->next != NULL)
			last = last->next;
		last->next = room;
		room->index = last->index + 1;
	}
	return (room);
}

/*
** Return room from room's array by room index
*/

t_room	*ft_room_get(t_room *rooms, int index)
{
	if (rooms == NULL)
		return (NULL);
	/* rooms->index != index можно заменить index-- != 0
	если  последовательность индексов никогда не будет нарушаться (без удаления комнат?)*/
	while (rooms && rooms->index != index)
		rooms = rooms->next;
	/* Если rooms->index != index, а список комнат закончился вернется null
	т.к. rooms = rooms->next на последней итерации запишет в rooms NULL*/
	return (rooms);
}

/*
** Frees an array of rooms
*/

void	ft_room_full_free(t_room **rooms)
{
	t_room	*current;
	t_room	*next;

	if (rooms == NULL)
		return ;
	current = *rooms;
	while (current)
	{
		next = current->next;
		current->name ? free(current->name) : NULL;
		current->input_links ? free(current->input_links) : NULL;
		current->output_links ? free(current->output_links) : NULL;
		free(current);
		current = next;
	}
	*rooms = NULL;
}