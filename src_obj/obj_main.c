/*
** main.c for  in /home/soto_a/test/test
** 
** Made by adam soto
** Login   <soto_a@epitech.net>
** 
** Started on  Thu Feb 25 21:25:43 2016 adam soto
** Last update Sun Feb 28 18:48:14 2016 adam soto
*/

#include "my_objdump.h"

char	*g_file_path;

int		open_check(const char *file_path)
{
  int		fd;
  struct stat	sb;

  if ((fd = open(g_file_path, O_RDONLY)) != -1)
    {
      fstat(fd, &sb);
      if (S_ISREG(sb.st_mode) && !S_ISDIR(sb.st_mode))
	return (fd);
      else
	{
	  fprintf(stderr,
		  "/usr/bin/objdump: Warning: '%s' is not an ordinary file\n",
		  file_path);
	}
    }
  else
    fprintf(stderr, "/usr/bin/objdump: '%s': No such file\n", file_path);
  exit(EXIT_FAILURE);
  return (-1);
}

int	main(int ac, char **av)
{
  int	i;

  i = 1;
  if (ac > 1)
    {
      while (av[i] != NULL)
        {
	  g_file_path = av[i];
          my_objdump(open_check(av[i]));
          i++;
        }
    }
  else
    {
      g_file_path = "a.out";
      my_objdump(open_check("a.out"));
    }
  return (EXIT_SUCCESS);
}
