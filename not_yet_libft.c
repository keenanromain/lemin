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
