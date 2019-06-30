/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lem_in.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larlyne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:57:12 by larlyne           #+#    #+#             */
/*   Updated: 2019/06/30 14:48:07 by rhealitt         ###   ########.fr       */
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
# include "../lib/libft/libft.h"
# include "../lib/libft/get_next_line.h"

typedef struct	s_room
{
	char			*name;
	int				x;
	int				y;

	struct s_link	*links;
	int				links_count;

	int				ant;
	int				weight;
	int				weight_difference;
	int				lock;
	char			closed;

	int				flags;

	struct s_room	*path_next;
	struct s_room	*path_prev;

	struct s_room	*next;
}				t_room;

typedef struct	s_link
{
	t_room			*room;
	struct s_link	*next;
}				t_link;

typedef struct	s_path
{
	int				length;
	t_room			*start;
	t_room			*end;

	int				order;

	struct s_path	*next;
}				t_path;

typedef struct	s_collision
{
	t_room				*old_room;
	t_room				*old_redirect;
	t_room				*to_redirect;

	int					state;
	int					id;

	struct s_collision	*prev;
	struct s_collision	*next;
}				t_collision;

typedef struct	s_lemin
{
	int				ants;
	int				ants_came;
	unsigned int	mean_length;
	unsigned int	depth;

	t_collision		*collisions;
	unsigned int	collisions_i;

	t_room			*start_room;
	t_room			*end_room;
	t_room			*rooms;
	unsigned int	rooms_count;

	t_path			*paths;
	unsigned int	paths_count;
}				t_lemin;

/*
** parse_lins.c
*/

int				ft_search_dup_link(t_room *room1, t_room *room2);
int				ft_parse_links(char *line, t_lemin *li, char *flag);
int				ft_split_link(char *line, char **name1, char **name2);

/*
** parse_rooms.c
*/

int 			ft_parse_rooms(int fd, t_lemin *li, t_lstr *lstr, int err);
int				ft_found_flag(t_lemin *li, t_room *room, char flag);
int				ft_validation(int fd, t_lemin *li, t_lstr *lstr);
void			ft_string_insert(t_lstr *lstr, char *str, int index);
int				ft_free_line(char *line);
int				ft_scan_li(t_lemin *li);
int				ft_solution(t_lemin *li);
int				ft_migration(t_lemin *li, t_lstr *lstr);

/*
** rooms.c
*/
void			ft_coordinate_room(t_room *room, char *line, int i);
int				ft_create_room(char *line, t_lemin *li, char *flag);
t_room			*ft_room_new(t_lemin *li, t_room **rooms);
void			ft_room_full_free(t_room **rooms);
void			ft_rooms_reset(t_room *rooms);

/*
** links.c
*/

void			ft_link_set(t_room *room1, t_room *room2);

/*
** paths.c
*/

t_path			*ft_path_new(t_path **paths);

/*
** collisions.c
*/

void			ft_collision_clear(t_lemin *li);
int				ft_check_collision(t_lemin *li, t_room *room);

/*
** collisions_2.c
*/

int				ft_path_cost(t_lemin *li, int depth);
void			ft_collision(t_lemin *li, t_room *room, t_room *coll_room,
					int depth);

/*
** lock.c
*/

void			ft_lock_paths(t_lemin *li);
#endif
