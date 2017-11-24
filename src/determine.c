#include "lemin.h"

void determine_path(t_path *path, int size)
{
  t_env *tmp;
  t_path *each;

  if (!path)
    return ;
  env = path->adjacent;
  while (env)
  {
    each = env->details;
    if (each && (each->len == -1 || each->len > size + 1))
    {
      if (g_max_depth < size + 1)
        g_max_depth = size + 1;
      each->len = size + 1;
      determine_path(each, each->len)
    }
    env = env->next;
  }
}

t_path  *closest_adjacent(t_path *path)
{
  t_env *env;
  t_path *best;

  env = path->adjacent;
  best = env->details;
  while (env)
  {
    if (env->details)
      if (env->details->len < best->len)
        best = env->details;
    env = env->next;
  }
  return (best)
}

void traverse_path(t_path *first, t_path *end, int i)
{
  t_path *tmp;
  int check;

  check = 0;
  while (first != end)
  {
    if (check > g_max_depth)
      error_event(5);
    if (!(tmp = closest_adjacent(first)))
      error_event(6)
    ft_printf("L%d-%s\n", i, tmp->name);
    check++;
    first = first->next;
  }
}
