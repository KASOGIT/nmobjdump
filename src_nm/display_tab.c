/*
** display_tab.c for  in /home/soto_a/nmobjdump/src_nm
** 
** Made by adam soto
** Login   <soto_a@epitech.net>
** 
** Started on  Sat Feb 27 12:05:28 2016 adam soto
** Last update Sat Feb 27 13:04:55 2016 adam soto
*/

#include "my_nm.h"

void	print_tab(t_el_sym **tab_sym, Elf64_Shdr *sec_hdr)
{
  char	c;
  int	i;

  i = 0;
  while (tab_sym[i] != NULL)
    {
      c = get_flag(tab_sym[i]->sym, sec_hdr);
      if (c != 'w' && c != 'U')
	printf("%016x %c %s\n", (unsigned)tab_sym[i]->sym->st_value,
	       c, tab_sym[i]->name);
      else
	printf("%18c %s\n", c, tab_sym[i]->name);
      i++;
    }
}
