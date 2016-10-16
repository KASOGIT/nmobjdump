/*
** my_nm.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_nmobjdump/src_nm
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Feb 26 12:51:04 2016 
** Last update Thu Mar  3 14:40:38 2016 
*/

#include "my_nm.h"

int	g_size;

int	err_trunc()
{
  fprintf(stderr, "/usr/bin/nm: %s: File truncated\n", g_file_path);
  return (0);
}

int	check_truncated(void *data_load, Elf64_Ehdr *elf_hdr, Elf64_Shdr *sec_hdr)
{
  int	i;

  i = 0;
  while (i < elf_hdr->e_shnum)
    {
      if ((void *)(data_load + sec_hdr[i].sh_offset + sec_hdr[i].sh_size )
          > (data_load + g_size))
        return (err_trunc());
      i++;
    }
  return (1);
}

void	act_on_sec(void *data_load, Elf64_Shdr *sec_hdr, Elf64_Ehdr *elf_hdr)
{
  unsigned char	*strtab;
  int		i;
  t_el_sym	**tab_sym;

  i = 0;
  while (i < elf_hdr->e_shnum)
    {
      if (sec_hdr[i].sh_type == SHT_SYMTAB)
	{
	  if (data_load + sec_hdr[sec_hdr[i].sh_link].sh_offset
	      < data_load + g_size)
	    {
	      strtab = (unsigned char *)((uint8_t *)data_load
		       + sec_hdr[sec_hdr[i].sh_link].sh_offset);
	      tab_sym = fill_tab_sym(data_load, sec_hdr, strtab, i);
	      print_tab(tab_sym, sec_hdr);
	    }
	}
      i++;
    }
}

void		get_elf_data_and_act(void *data_load, Elf64_Ehdr *elf_hdr)
{
  Elf64_Shdr	*sec_hdr;

  if (data_load + elf_hdr->e_shoff < data_load + g_size)
    {
      sec_hdr = (Elf64_Shdr *)(data_load + elf_hdr->e_shoff);
      /* if (check_truncated(data_load, elf_hdr, sec_hdr)) */
      /* 	{ */
	  act_on_sec(data_load, sec_hdr, elf_hdr);
	/* } */
    }
  else
    err_trunc();
}

void		my_nm(int fd)
{
  void		*data_load;
  Elf64_Ehdr	*elf_hdr;

  g_size = get_filesize(fd);
  if ((data_load = mmap(NULL, get_filesize(fd),
			PROT_READ, MAP_SHARED, fd, 0)) != NULL)
    {
      elf_hdr = (Elf64_Ehdr *)data_load;
      if (check_elf_fmt(elf_hdr->e_ident))
	get_elf_data_and_act(data_load, elf_hdr);
      else if (check_ar_fmt(data_load))
	parse_ar_file_and_act(data_load, fd);
      else
	fprintf(stderr, "/usr/bin/nm: %s: File format not recognized\n",
		g_file_path);
      close(fd);
    }
}
