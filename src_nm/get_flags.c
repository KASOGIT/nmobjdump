/*
** get_flags.c for  in /home/soto_a/nmobjdump/src_nm
** 
** Made by adam soto
** Login   <soto_a@epitech.net>
** 
** Started on  Sat Feb 27 12:06:51 2016 adam soto
** Last update Sat Feb 27 15:34:01 2016 
*/

#include "my_nm.h"

static char	get_flag2(Elf64_Sym *sym, Elf64_Shdr *shdr, char *c)
{
  if (sym->st_shndx == SHN_ABS)
    *c = 'A';
  else if (sym->st_shndx == SHN_COMMON)
    *c = 'C';
  else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
	   && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    *c = 'D';
  else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
	   && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    *c = 'T';
  else if (shdr[sym->st_shndx].sh_type == SHT_DYNAMIC)
    *c = 'D';
  else if ((shdr[sym->st_shndx].sh_type == SHT_FINI_ARRAY ||
	    shdr[sym->st_shndx].sh_type == SHT_INIT_ARRAY) &&
	    shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    *c = 'T';
  else if (shdr[sym->st_shndx].sh_type == SHT_NOBITS
	   && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    *c = 'B';
  else if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
	   && (shdr[sym->st_shndx].sh_flags == SHF_ALLOC
	   || shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_MERGE)))
    *c = 'R';
  else
    *c = '?';
  return (*c);
}

char	get_flag(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char	c;

  if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
    c = 'u';
  else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK &&
	   ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
    {
      c = 'V';
      if (sym->st_shndx == SHN_UNDEF)
        c = 'v';
    }
  else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
    {
      c = 'W';
      if (sym->st_shndx == SHN_UNDEF)
        c = 'w';
    }
  else if (sym->st_shndx == SHN_UNDEF)
    c = 'U';
  else
    get_flag2(sym, shdr, &c);
  if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
    c += 32;
  return (c);
}
