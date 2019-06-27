#include "../include/ft_lem_in.h"

t_path	*ft_path_new(t_path **paths)
{
	t_path	*path;
	t_path	*pth;

	if (paths == NULL)
		return (NULL);
	if ((path = (t_path*)ft_memalloc(sizeof(t_path))) == NULL)
		return (NULL);
	if (*paths == NULL)
		*paths = path;
	else
	{
		pth = *paths;
		while (pth->next != NULL)
			pth = pth->next;
		pth->next = path;
	}
	return (path);
}