/*
** sort_tab.c for  in /home/soto_a/nmobjdump/src_nm
** 
** Made by adam soto
** Login   <soto_a@epitech.net>
** 
** Started on  Sat Feb 27 12:00:23 2016 adam soto
** Last update Sat Feb 27 13:14:09 2016 adam soto
*/

#include "my_nm.h"

int		get_size_tab(Elf64_Sym *start, Elf64_Sym *end)
{
  int		count;
  Elf64_Sym	*tmp;

  count = 0;
  tmp = start;
  while (tmp < end)
    {
      tmp++;
      count++;
    }
  return (count);
}

Elf64_Sym	*get_next_sym(Elf64_Sym *current, Elf64_Sym *last)
{
  current++;
  if (current < last)
    return (current);
  return (NULL);
}

static t_el_sym	*create_new_el(unsigned char *name, Elf64_Sym *sym)
{
  t_el_sym	*new;

  if ((new = malloc(sizeof(t_el_sym))) == NULL)
    fatal_err("Error");
  new->name = name;
  new->sym = sym;
  return (new);
}

t_el_sym	**fill_tab_sym(void *data_load, Elf64_Shdr *sec_hdr,
			       unsigned char *strtab, int pos)
{
  t_el_sym	**tab_sym;
  Elf64_Sym	*sym_current;
  Elf64_Sym	*sym_end;
  int		i;

  i = 0;
  sym_current = (Elf64_Sym *)((uint8_t *)data_load + sec_hdr[pos].sh_offset);
  sym_end = (Elf64_Sym *)((uint8_t *)sym_current + sec_hdr[pos].sh_size);
  if ((tab_sym = malloc(sizeof(t_el_sym *)
			* (get_size_tab(sym_current, sym_end) + 1))) == NULL)
    fatal_err("Error");
  if (sym_current->st_shndx != SHN_ABS && strtab[sym_current->st_name] != '\0')
    tab_sym[i++] = create_new_el(&strtab[sym_current->st_name], sym_current);
  while ((sym_current = get_next_sym(sym_current, sym_end)) != NULL)
    {
      if (sym_current->st_shndx != SHN_ABS
	  && strtab[sym_current->st_name] != '\0')
	tab_sym[i++] = create_new_el(&strtab[sym_current->st_name], sym_current);
    }
  tab_sym[i] = NULL;
  sort_tab_sym(tab_sym, sec_hdr);
  return (tab_sym);
}
