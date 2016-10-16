/*
** ar.c for  in /home/soto_a/test/test
** 
** Made by adam soto
** Login   <soto_a@epitech.net>
** 
** Started on  Thu Feb 25 21:36:02 2016 adam soto
** Last update Thu Mar  3 14:39:36 2016 
*/

#include "my_objdump.h"

void	*g_ptr;

int	check_ar_fmt(void *data_load)
{
  char	*magic;

  magic = (char *)data_load;
  if (strncmp(magic, ARMAG, strlen(ARMAG)) == 0)
    return (1);
  return (0);
}

void		get_elf_data_and_act(void *data_load, Elf64_Ehdr *elf_hdr,
				     char const *file_path)
{
  Elf64_Shdr	*sec_hdr;
  char		*strtab;

  if (data_load + elf_hdr->e_shoff < data_load + g_size)
    {
      sec_hdr = (Elf64_Shdr *)(data_load + elf_hdr->e_shoff);
      if (data_load + sec_hdr[elf_hdr->e_shstrndx].sh_offset
	  < data_load + g_size)
	{
	  strtab = (char *)(data_load + sec_hdr[elf_hdr->e_shstrndx].sh_offset);
	  /* if (check_truncated(data_load, elf_hdr, sec_hdr)) */
	  /*   { */
	      display_hdr_info(file_path, elf_hdr, sec_hdr);
	      display_section_data(sec_hdr, strtab, data_load, elf_hdr);
	    /* } */
	}
      else
	err_trunc();
    }
  else
    err_trunc();
}

char	*get_elf_name(char *name, char *s_tab_name)
{
  char	*get_name;
  int	i;

  i = 0;
  get_name = strdup(name);
  if (strncmp(name, "/", 1) == 0)
    {
      free(get_name);
      if ((void *)(s_tab_name + atoi(name + 1)) > g_ptr + g_size)
	fatal_err("truncated file");
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
  g_file_path = get_name;
  if (ptr + i + sizeof(struct ar_hdr) < ptr + g_size)
    {
      elf_hdr = (Elf64_Ehdr *)(ptr + i + sizeof(struct ar_hdr));
      if (check_elf_fmt(elf_hdr->e_ident))
	get_elf_data_and_act(ptr + i + sizeof(struct ar_hdr),
			     elf_hdr, get_name);
      else
 	fprintf(stderr, "/usr/bin/objdump: %s: File format not recognized\n",
		name);
    }
  else
    err_trunc();
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

  i = 0;
  ptr = (data_load + SARMAG);
  while (i < get_filesize(fd) - 8)
    {
      /* if (ptr + i < ptr + g_size) */
      /* 	return (err_ar()); */
      ar_hdrs = (ptr + i);
      memset(nb, 0, 11);
      memset(name, 0, 17);
      strncpy(nb, ar_hdrs->ar_size, 11);
      strncpy(name, ar_hdrs->ar_name, 17);
      //g_size = atoi(nb);
      if (i != 0)
        {
	  if (ptr + i + sizeof(struct ar_hdr) < data_load + get_filesize(fd))
	    {
	      g_ptr = ptr;
	      if (strncmp(name, "//", 2) == 0)
		s_tab_name = (char *)(ptr + i + sizeof(struct ar_hdr));
	      else
		act_data_ar(ptr, name, i, s_tab_name);
	    }
	  else
	    err_trunc();
        }
      i += sizeof(struct ar_hdr) + atoi(nb);
    }
}
