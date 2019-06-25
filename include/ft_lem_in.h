/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lem_in.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:57:12 by larlyne           #+#    #+#             */
/*   Updated: 2019/06/24 12:07:42 by rhealitt         ###   ########.fr       */
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
# define FT_NO_PATHS 10
# define FT_MEMORY 11
# define FT_DUP_NAME 12
# define FT_DUP_COORDINATES 13
# define FT_DUP_ROOM 14
# define FT_NO_DATA 15
# define FT_NO_FLAGS 0
# define FT_START 1
# define FT_END (1 << 1)
# define FT_ANT (1 << 2)
# define FT_BFS_MARK (1 << 3)
# define FT_ERROR (1 << 4)
# define FT_DIRECTION 0
# define FT_ALL_LINK 1
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct	s_room
{
	char			*name;
	int				x;
	int				y;
	struct s_link	*input_links;
	int				input_count;
	struct s_link	*output_links;
	int				output_count;
	char			flags;
	int				ant;
	int				index;
	int				bfs_level;
	struct s_room	*next;
}				t_room;

typedef struct	s_link
{
	t_room			*linked_room;
	char			link_type;
	struct s_link	*next;
}				t_link;

typedef struct	s_path
{
	int				length;
	t_room			*start;
	t_room			*end;
	struct s_path	*next;
}				t_path;

typedef struct	s_lemin
{
	unsigned int	ants;
	unsigned int	ants_on_a_way;
	t_room	*rooms;
	t_room	*start_room;
	t_room	*end_room;
	t_path	*paths;
}				t_lemin;

int		ft_validation(int fd, t_lemin *li, t_lstr *lstr);
void		ft_string_insert(t_lstr *lstr, char *str, int index);
/*
** parse_lins.c
*/

int		ft_parse_links(char *line, t_lemin *li, char *flag);

/*
** parse_rooms.c
*/

int 	ft_parse_rooms(int fd, t_lemin *li, t_lstr *lstr);
void	ft_string_insert(t_lstr *lstr, char *str, int index);
int		ft_solution(t_lemin *li);
int		ft_migration(t_lemin *li, t_lstr *lstr);

/*
** rooms.c
*/

t_room	*ft_room_new(t_room **rooms);
t_room	*ft_room_get(t_room *rooms, int index);
void	ft_room_full_free(t_room **rooms);

/*
** links.c
*/

void	ft_link_set(t_room *from, t_room *to);
void	ft_link_unset_dir(t_room *from, t_room *to);
void	ft_link_restore(t_room *rooms);

/*
** paths.c
*/

t_path	*ft_path_new(t_path **paths, t_room *start, t_room *end, int length);

/*
** bfs.c
*/

int		ft_bfs(t_lemin *li);

#endif
