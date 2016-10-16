/*
** my_objdump.c for  in /home/soto_a/test/test
** 
** Made by adam soto
** Login   <soto_a@epitech.net>
** 
** Started on  Mon Feb 22 16:40:21 2016 adam soto
** Last update Sun Feb 28 18:32:50 2016 adam soto
*/

#include "my_objdump.h"

int	g_size;

void		my_objdump(int fd)
{
  void		*data_load;
  Elf64_Ehdr	*elf_hdr;

  g_size = get_filesize(fd);
  if ((data_load = mmap(NULL, get_filesize(fd),
			PROT_READ, MAP_SHARED, fd, 0)) != NULL)
    {
      elf_hdr = (Elf64_Ehdr *)data_load;
      if (check_elf_fmt(elf_hdr->e_ident))
	get_elf_data_and_act(data_load, elf_hdr, g_file_path);
      else if (check_ar_fmt(data_load))
	{
	  printf("In archive %s:\n", g_file_path);
	  parse_ar_file_and_act(data_load, fd);
	}
      else
	fprintf(stderr, "/usr/bin/objdump: %s: File format not recognized\n",
		g_file_path);
      close(fd);
    }
}
