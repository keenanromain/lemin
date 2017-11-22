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
