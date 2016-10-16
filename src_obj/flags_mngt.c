/*
** flags_mngt.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_nmobjdump/src_obj
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Feb 27 17:29:27 2016 
** Last update Sat Feb 27 17:31:32 2016 
*/

#include "my_objdump.h"

static t_flags  g_flags[] =
  {
    {BFD_NO_FLAGS, "BFD_NO_FLAGS"},
    {HAS_RELOC, "HAS_RELOC"},
    {EXEC_P, "EXEC_P"},
    {HAS_LINENO, "HAS_LINENO"},
    {HAS_DEBUG, "HAS_DEBUG"},
    {HAS_SYMS, "HAS_SYMS"},
    {HAS_LOCALS, "HAS_LOCALS"},
    {DYNAMIC, "DYNAMIC"},
    {WP_TEXT, "WP_TEXT"},
    {D_PAGED, "D_PAGED"},
    {-1, NULL}
  };

void	show_flags(int flags)
{
  int	i;
  int	check;

  i = 0;
  check = 1;
  while (g_flags[i].name != NULL)
    {
      if (flags & g_flags[i].flag)
	{
	  if (check)
	    check = 0;
	  else
	    printf(", ");
	  printf("%s", g_flags[i].name);
	}
      i++;
    }
  printf("\n");
}

int	get_flags(Elf64_Ehdr *elf_hdr, Elf64_Shdr *sec_hdr)
{
  int	i;
  int	flags;

  flags = 0;
  i = -1;
  if (elf_hdr->e_phnum != 0)
    flags |= D_PAGED;
  while (++i < elf_hdr->e_shnum)
    {
      if (sec_hdr[i].sh_type == SHT_SYMTAB || sec_hdr[i].sh_type == SHT_DYNSYM)
	flags |= HAS_SYMS;
      if (sec_hdr[i].sh_type == SHT_REL || sec_hdr[i].sh_type == SHT_RELA)
	flags |= HAS_RELOC;
    }
  if (elf_hdr->e_type == ET_EXEC)
    {
      flags &= ~HAS_RELOC;
      flags |= EXEC_P;
    }
  else if (elf_hdr->e_type == ET_DYN)
    {
      flags &= ~HAS_RELOC;
      flags |= DYNAMIC;
    }
  return (flags);
}
