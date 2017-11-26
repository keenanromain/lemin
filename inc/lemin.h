#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdbool.h>

# define START  "##start"
# define END    "##end"
# define ERR_0  "Failed to Allocate Memory with Malloc"
# define ERR_1  "Parsing Failure"
# define ERR_2  "No starting or no ending position"
# define ERR_3  "Did not recieve ants"
# define ERR_4  "Pipe Error"
# define ERR_5  "Incorrect number of rooms/links"
# define ERR_6  "Invalid path"

typedef struct  s_path t_path;
typedef struct  s_env t_env;

struct s_path
{
  char    *name;
  char    *attr;
  int     x;
  int     y;
  int     len;
  t_env   *adjacent;
  t_path  *next;
};

struct s_env
{
  t_path  *details;
  t_env   *next;
};

char            *g_following_attr;
int             g_ant_index;
t_path          *g_full_path;

int             main(void);
void            error_event(int errno);
int             parse_into_globals(char *line);
char            *read_line(int fd, char *tmp);
void            parse_room(char *s);
void            parse_pipe(char *s);
void            push_path_top(t_path **head, t_path *copy);
void            push_env_top(t_env **head, t_path *copy);
t_path          *find_name_in_path(t_path *path, char *desired);
t_path          *find_attr_in_path(t_path *path, char *desired);
void            determine_path(t_path *path, int size);
t_path          *closest_adjacent(t_path *path);
void            traverse_path(t_path *first, t_path *end, int i);

#endif
