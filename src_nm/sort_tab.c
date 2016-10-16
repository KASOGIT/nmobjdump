/*
** util_sort_tab.c for  in /home/soto_a/nmobjdump/src_nm
** 
** Made by adam soto
** Login   <soto_a@epitech.net>
** 
** Started on  Sat Feb 27 12:01:40 2016 adam soto
** Last update Sat Feb 27 13:16:08 2016 adam soto
*/

#include "my_nm.h"

int	compare_sym(t_el_sym *el1, t_el_sym *el2, Elf64_Shdr *sec_hdr)
{
  char	*ep1;
  char	*ep2;
  int	ret;

  ep1 = epur_name((char *)el1->name);
  ep2 = epur_name((char *)el2->name);
  ret = strcmp(ep1, ep2);
  free(ep1);
  free(ep2);
  if (ret == 0)
    return ((int)(get_flag(el1->sym, sec_hdr) - get_flag(el2->sym, sec_hdr)));
  return (ret);
}

void		sort_tab_sym(t_el_sym **tab, Elf64_Shdr *sec_hdr)
{
  int		i;
  t_el_sym	*tmp;

  i = 0;
  while (tab[i + 1] != NULL)
    {
      if (compare_sym(tab[i], tab[i + 1], sec_hdr) > 0)
        {
          tmp = tab[i];
          tab[i] = tab[i + 1];
          tab[i + 1] = tmp;
          i = 0;
        }
      else
        i++;
    }
}

char	*epur_name(char const *str)
{
  char	*epur;
  int	i;
  int	j;

  i = 0;
  j = 0;
  if ((epur = malloc(sizeof(char) * strlen(str))) == NULL)
    fatal_err("Error");
  while (str[i] != '\0')
    {
      if (str[i] != '_' && str[i] != '@')
        {
          epur[j] = str[i];
          if (epur[j] >= 'A' && epur[j] <= 'Z')
            epur[j] += 32;
          j++;
        }
      i++;
    }
  epur[j] = '\0';
  return (epur);
}
