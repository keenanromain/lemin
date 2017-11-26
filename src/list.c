#include "../inc/lemin.h"

void push_path_top(t_path **head, t_path *copy)
{
  t_path *new;

  new = (t_path *)malloc(sizeof(t_path));
  ft_memcpy(new, copy, sizeof(*copy));
  new->next = *head;
  *head = new;
}

void push_env_top(t_env **head, t_path *copy)
{
  t_env *new;

  new = (t_env *)malloc(sizeof(t_env));
  new->details = copy;
  new->next = *head;
  *head = new;
}

t_path *find_name_in_path(t_path *path, char *desired)
{
  while (path)
  {
    if (path->name)
      if (ft_strcmp(path->name, desired) == 0)
        return (path);
    path = path->next;
  }
  return ((void *)0);
}

t_path *find_attr_in_path(t_path *path, char *desired)
{
  while (path)
  {
    if (path->attr)
      if (ft_strcmp(path->attr, desired) == 0)
        return (path);
    path = path->next;
  }
  return ((void *)0);
}
