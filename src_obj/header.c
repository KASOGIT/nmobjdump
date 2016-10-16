/*
** header.c for  in /home/soto_a/test/test
** 
** Made by adam soto
** Login   <soto_a@epitech.net>
** 
** Started on  Thu Feb 25 21:28:41 2016 adam soto
** Last update Sun Feb 28 19:51:21 2016 adam soto
*/

#include "my_objdump.h"

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

char	*get_class(int id)
{
  if (id == 1)
    return ("elf32");
  else if (id == 2)
    return ("elf64");
  else
    fatal_err("unknow class");
  return (NULL);
}

char	*get_machine(int id)
{
  if (id == EM_SPARC)
    return ("sun");
  else if (id == EM_386)
    return ("i386");
  else if (id == EM_X86_64)
    return ("x86-64");
  else if (id == EM_PPC64)
    return ("ppc64");
  else if (id == EM_PPC)
    return ("ppc");
  else
    fatal_err("unknow machine");
  return (NULL);
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

void	display_hdr_info(char const *file_path,
			 Elf64_Ehdr *elf_hdr, Elf64_Shdr *sec_hdr)
{
  int	flags;

  printf("\n%s:     ", file_path);
  printf("file format %s-%s\n", get_class(elf_hdr->e_ident[EI_CLASS]),
	 get_machine(elf_hdr->e_machine));
  flags = get_flags(elf_hdr, sec_hdr);
  printf("architecture: i386:x86-64, flags 0x%08x:\n", flags);
  show_flags(flags);
  if (elf_hdr->e_entry != 0)
    printf("start address %#018x\n\n", (unsigned int)elf_hdr->e_entry);
  else
    printf("start address 0x%#016x\n\n", (unsigned int)elf_hdr->e_entry);
}
