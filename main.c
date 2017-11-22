typedef struct s_path t_path;
typedef struct s_env t_env;

struct s_path
{
  char    *name;
  char    *attr;
  int     x;
  int     y;
  int     len;
  t_env   *adjacent;
  t_path  *next;
}

struct s_env
{
  t_path  *details;
  t_env   *next;
  //probably will also store global variables
  //need to refactor code first
}

char    *g_following_attr = 0;
int     g_ant_index = 0;
t_path  *g_full_path = 0;

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
  exit(-1);
}

int   main(void)
{
  t_path *first_pos;
  t_path *last_pos;

  if (!parse_into_globals(NULL))
    error_event(1); //error_event(0) is for malloc
  if (!(first_pos = find_attr_in_path(g_full_path, START)) \
  || !(last_pos = find_attr_in_path(g_full_path, END)))
    error_event(2);
  determine_path(last_pos, (last_pos->len = 0));
  if (g_ant_index) //might be able to discard this check based on return from parser
    while (g_ant_index--) //it assumes both globals are required which I'm not certain on
      traverse_path(first_pos, last_pos)
  else //might be able to discard this check based on return from parser
    error_event(3);
  return (0);
}
