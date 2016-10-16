/*
** utils_obj.c for  in /home/soto_a/test/test
** 
** Made by adam soto
** Login   <soto_a@epitech.net>
** 
** Started on  Thu Feb 25 22:06:56 2016 adam soto
** Last update Sun Feb 28 21:12:29 2016 
*/

#include "my_objdump.h"

int	get_filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}

void	fatal_err(char const *err_msg)
{
  fprintf(stderr, "%s\n", err_msg);
  exit(EXIT_FAILURE);
}

int		check_fmt_addr(Elf64_Shdr *sec_hdr, int i)
{
  size_t	j;

  j = sec_hdr[i].sh_offset;
  while (j < sec_hdr[i].sh_size)
    {
      if (sec_hdr[i].sh_addr + j > 65535)
        return (1);
      j += 16;
    }
  return (0);
}

int	err_trunc()
{
  fprintf(stderr, "/usr/bin/objdump: %s: File truncated\n", g_file_path);
  return (0);
}

void	err_ar()
{
  fprintf(stderr, "/usr/bin/objdump: %s: Malformed archive\n", g_file_path);
}
