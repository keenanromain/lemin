#include "lemin.h"

void error_event(int errno)
{
  if (errno == 0)
    ft_putstr_fd(ERR_0, 2); // malloc failure
  else if (errno == 1)
    ft_putstr_fd(ERR_1, 2); // parsing failure
  else if (errno == 2)
    ft_putstr_fd(ERR_2, 2); // no starting or no ending position
  else if (errno == 3)
    ft_putstr_fd(ERR_3, 2); // received no ants
  else if (errno == 4)
    ft_putstr_fd(ERR_4, 2); // pipe error
  else if (errno == 5)
    ft_putstr_fd(ERR_5, 2); // depth failure
  exit(-1);
}

g_following_attr = 0;
g_ant_index = 0;
g_max_depth = 0;
g_full_path = 0;

int   main(void)
{
  t_path  *first_pos;
  t_path  *last_pos;
  int     i;

  if (!parse_into_globals(NULL))
    error_event(1); //error_event(0) is for malloc
  if (!(first_pos = find_attr_in_path(g_full_path, START)) \
  || !(last_pos = find_attr_in_path(g_full_path, END)))
    error_event(2);
  determine_path(last_pos, (last_pos->len = 0));
  i = 0;
  if (g_ant_index) //might be able to discard this check based on return from parser
    while (g_ant_index--) //it assumes both globals are required which I'm not certain on
      traverse_path(first_pos, last_pos, i++)
  else //might be able to discard this check based on return from parser
    error_event(3);
  return (0);
}