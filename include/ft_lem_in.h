/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lem_in.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:57:12 by larlyne           #+#    #+#             */
/*   Updated: 2019/06/20 16:57:14 by larlyne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEM_IN_H
# define FT_LEM_IN_H
# define FT_OK 0
# define FT_NO_START 1
# define FT_ONE_MORE_START 2
# define FT_NO_END 3
# define FT_ONE_MORE_END 4
# define FT_NO_ANTS 5
# define FT_NO_ROOMS 6
# define FT_NO_TUNNEL 7
# define FT_WRONG_FORMAT 8
# define FT_NO_PATH_TO_END 9
# define FT_MEMORY 10
# define FT_NO_FLAGS 0
# define FT_START 1
# define FT_END (1 << 1)
# define FT_ANT (1 << 2)
# define FT_BFS_MARK (1 << 3)
# define FT_DIRECTION 0
# define FT_ALL_LINK 1
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include "libft.h"

typedef struct	s_lemin
{
	uint		ants;
	t_room	*rooms;
	/*char	**links_matrix;*/
	t_path	*paths;
}				t_lemin;

typedef struct	s_room
{
	char		*name;
	int			x;
	int			y;
	short int	*input_links;
	int			input_count;
	short int	*output_links;
	int			output_count;
	char		type;
	char		ant;
	int			index;
	int			bfs_level;
	t_room		*next;
}				t_room;

typedef struct	s_path
{
	int		length;
	int		start_index;
	int		end_index;
	t_path	*next;
}				t_path;

int		ft_validation(int fd, t_lemin *li, t_lstr *lstr);
int		ft_solution(t_lemin *li);
int		ft_migration(t_lemin *li, t_lstr *lstr);

/*
** rooms.c
*/

t_room	*ft_room_new(t_room **rooms);
t_room	*ft_room_get(t_room *rooms, int index);
t_room	*ft_room_get_where(t_room *rooms, int (*f)(t_room*));
void	ft_room_full_free(t_room **rooms);

void	ft_link_set(t_room *rooms, int room_i1, int room_i2);
void	ft_link_unset(t_room *rooms, int from, int to, char unset_type);
void	ft_link_restore(t_room *rooms);

/*
** bfs.c
*/

int		ft_bfs(t_lemin *li);

#endif