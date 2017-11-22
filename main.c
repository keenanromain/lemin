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
  new->path = copy
  new->next = *head
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
  return ((void *)0)
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
  return ((void *)0)
}

int   ft_strcnum(char *s, char c)
{
  int count;
  int i;

  count = 0;
  i = -1;
  while (s[++i])
    if (s[i] == c)
      count++;
  return (count);
}

char  *read_line(int fd, char *tmp) //see about just using get next line
{
  char *line;
  char buffer[2];
  int r;

  line = ft_strnew(0);
  ft_bzero(buffer, 2);
  r = 0;
  while(buffer[0] != '\n')
  {
    if ((r = read(fd, buffer, 1)) <= 0)
      error_event(1); //reading error
    tmp = ft_strjoin(line, buffer);
    ft_strdel(&line);
    line = tmp;
  }
  *ft_strchr(line, '\n') = 0;
  return (line);
}

void parse_room(char *s)
{
  t_path path;
  char **tab;

  tab = ft_strsplit(s, ' ');
  path.name = tab[0];
  path.x = tab[1];
  path.y = tab[2];
  path.len = -1;
  path.attr = g_following_attr;
  path.adjacent = NULL;
  path.next = NULL;
  g_following_attr = NULL;
  push_path_top(&g_full_path, &path);
  ft_printf("%s %d %d\n", path.name, path.x, path.y);
}

void parse_pipe(char *s)
{
  t_path left;
  t_path right;
  char **tab;

  tab = ft_strsplit(s, '-');
  left = find_name_in_path(g_full_path, s[0]);
  right = find_name_in_path(g_full_path, s[1]);
  if (!left || !right)
    error_event(4);
  push_env_top(&left->adjacent, left);
  push_env_top(&right->adjacent, right);
  ft_printf("%s-%s", s[0], s[1]);
}

int   parse_into_globals(char *line)
{
    while (line = read_line(STDIN_FILENO, NULL)
    && ft_strlen(line))
    {
      if (line[0] == '#')
      {
        if (line[1] == '#')
          g_following_attr = ft_strdup(line);
        ft_printf("%s\n", line);
      }
      else if (ft_strcnum(line, ' ') == 2)
        parse_room(line);
      else if (!ft_strcnum(line, ' ') && ft_strcnum(line, '-'))
        parse_pipe(line);
      else if (!ft_strcnum(line, ' ') && ft_numlen(line) == ft_strlen(line))
      {
            g_ant_index = ft_atoi(line);
            ft_printf("%d\n", g_ant_index);
      }
      ft_strdel(&line);
    }
    return (g_ant_index && g_following_attr);
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
