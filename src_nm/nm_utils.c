/*
** nm_utils.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_nmobjdump/src_nm
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Feb 27 14:25:16 2016 
** Last update Sat Feb 27 14:26:56 2016 
*/

#include "my_nm.h"

int	get_filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}

void	fatal_err(char const *err_msg)
{
  fprintf(stderr, "%s\n", err_msg);
  exit(EXIT_FAILURE);
}

int	check_elf_fmt(unsigned char *e_ident)
{
  if (e_ident[EI_MAG0] != 0x7f
            || e_ident[EI_MAG1] != 'E'
            || e_ident[EI_MAG2] != 'L'
      || e_ident[EI_MAG3] != 'F')
    {
      return (0);
    }
  return (1);
}

int	check_ar_fmt(void *data_load)
{
  char	*magic;

  magic = (char *)data_load;
  if (strncmp(magic, ARMAG, strlen(ARMAG)) == 0)
    return (1);
  return (0);
}
