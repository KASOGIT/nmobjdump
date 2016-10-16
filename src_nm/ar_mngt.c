/*
** ar_mngt.c for  in /home/soto_a/nmobjdump/src_nm
** 
** Made by adam soto
** Login   <soto_a@epitech.net>
** 
** Started on  Fri Feb 26 23:13:28 2016 adam soto
** Last update Sun Feb 28 15:27:48 2016 
*/

#include "my_nm.h"

char	*get_elf_name(char *name, char *s_tab_name)
{
  char	*get_name;
  int	i;

  i = 0;
  get_name = strdup(name);
  if (strncmp(name, "/", 1) == 0)
    {
      free(get_name);
      get_name = strdup(s_tab_name + atoi(name + 1));
    }
  while (get_name[i] != '/')
    i++;
  get_name[i] = '\0';
  return (get_name);
}

void		act_data_ar(void *ptr, char *name, int i, char *s_tab_name)
{
  char		*get_name;
  Elf64_Ehdr	*elf_hdr;

  get_name = get_elf_name(name, s_tab_name);
  elf_hdr = (Elf64_Ehdr *)(ptr + i + sizeof(struct ar_hdr));
  if (check_elf_fmt(elf_hdr->e_ident))
    {
      printf("\n%s:\n", get_name);
      get_elf_data_and_act(ptr + i + sizeof(struct ar_hdr),
			   elf_hdr);
    }
  else
    fprintf(stderr, "/usr/bin/objdump: %s: File format not recognized\n",
	    name);
  free(get_name);
}

void		parse_ar_file_and_act(void *data_load, int fd)
{
  struct ar_hdr	*ar_hdrs;
  char		*s_tab_name;
  int		i;
  char		nb[11];
  char		name[17];
  void		*ptr;

  ptr = (data_load + SARMAG);
  i = 0;
  while (i < get_filesize(fd) - 8)
    {
      ar_hdrs = (ptr + i);
      memset(nb, 0, 11);
      memset(name, 0, 17);
      strncpy(nb, ar_hdrs->ar_size, 11);
      strncpy(name, ar_hdrs->ar_name, 17);
      if (i != 0)
        {
	  if (strncmp(name, "//", 2) == 0)
	    s_tab_name = (char *)(ptr + i + sizeof(struct ar_hdr));
	  else
	    act_data_ar(ptr, name, i, s_tab_name);
	}
      i += sizeof(struct ar_hdr) + atoi(nb);
    }
}
