/*
** fmt_display.c for  in /home/soto_a/test/test
** 
** Made by adam soto
** Login   <soto_a@epitech.net>
** 
** Started on  Thu Feb 25 21:32:09 2016 adam soto
** Last update Sun Feb 28 17:57:32 2016 adam soto
*/

#include "my_objdump.h"

void	display_char_readable(unsigned char *sub, int count)
{
  int	i;

  i = 0;
  printf(" ");
  while (i != 16)
    {
      if (i < count)
        {
          if (sub[i] >= 32 && sub[i] <= 126)
            printf("%c", sub[i]);
          else
            printf(".");
        }
      else
        printf(" ");
      i++;
    }
  printf("\n");
}

int	is_displayable(char *sec_name)
{
  if (strcmp(sec_name, ".shstrtab") != 0
      && strcmp(sec_name, ".symtab") != 0
      && strcmp(sec_name, ".strtab") != 0
      && strcmp(sec_name, ".bss") != 0)
    {
      return (1);
    }
  return (0);
}

int		format_and_display(int start, int max, unsigned char *mem)
{
  int		count;
  int		i;
  unsigned char	sub[17];

  count = 0;
  while (count != 16 && start != max)
    {
      sub[count] = mem[start];
      printf("%.2x", sub[count]);
      count++;
      start++;
      if (count % 4 == 0)
        printf(" ");
    }
  i = count;
  while (i != 16)
    {
      printf("  ");
      i++;
      if (i % 4 == 0)
        printf(" ");
    }
  display_char_readable(sub, count);
  return (start);
}

void	fmt_sec_and_display(Elf64_Shdr *sec_hdr, char *strtab,
			    void *data_load, int i)
{
  int	j;

  j = 0;
  printf("Contents of section %s:\n", &strtab[sec_hdr[i].sh_name]);
  while ((unsigned int)j < sec_hdr[i].sh_size)
    {
      if (check_fmt_addr(sec_hdr, i))
	printf(" %.5x ", (unsigned int)(sec_hdr[i].sh_addr + j));
      else
	printf(" %.4x ", (unsigned int)(sec_hdr[i].sh_addr + j));
      j = format_and_display(j, sec_hdr[i].sh_size,
			     (unsigned char *)(data_load + sec_hdr[i].sh_offset));
    }
}

void		display_section_data(Elf64_Shdr *sec_hdr, char *strtab,
				     void *data_load, Elf64_Ehdr *elf_hdr)
{
  int		i;
  uint16_t	e_type;

  i = 0;
  e_type = elf_hdr->e_type;
  while (i < elf_hdr->e_shnum)
    {
      if (sec_hdr[i].sh_size > 0)
        {
          if (is_displayable(&strtab[sec_hdr[i].sh_name]))
            {
              if (((e_type == ET_CORE || e_type == ET_REL)
                   && strncmp(&strtab[sec_hdr[i].sh_name],
                              ".rela", strlen(".rela")) != 0)
                  || (e_type == ET_EXEC || e_type == ET_DYN))
                {
                  fmt_sec_and_display(sec_hdr, strtab, data_load, i);
                }
            }
        }
      i++;
    }
}
