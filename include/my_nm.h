/*
** my_nm.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_nmobjdump/src_nm
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Feb 26 12:47:24 2016 
** Last update Sun Feb 28 18:48:52 2016 adam soto
*/

#ifndef MYNM_H_
#define MYNM_H_

#include <ar.h>
#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "flags.h"

typedef struct	s_el_sym
{
  unsigned char	*name;
  Elf64_Sym	*sym;
}		t_el_sym;

extern int	g_size;
extern char	*g_file_path;

void	my_nm(int fd);
char	*get_elf_name(char *name, char *s_tab_name);
void	act_data_ar(void *ptr, char *name, int i, char *s_tab_name);
void	parse_ar_file_and_act(void *data_load, int fd);
void	get_elf_data_and_act(void *data_load, Elf64_Ehdr *elf_hdr);
void	print_tab(t_el_sym **tab_sym, Elf64_Shdr *sec_hdr);
t_el_sym	**fill_tab_sym(void *data_load, Elf64_Shdr *sec_hdr,
			       unsigned char *strtab, int pos);
int	get_size_tab(Elf64_Sym *start, Elf64_Sym *end);
void	sort_tab_sym(t_el_sym **tab, Elf64_Shdr *sec_hdr);
int	compare_sym(t_el_sym *el1, t_el_sym *el2, Elf64_Shdr *sec_hdr);
char	get_flag(Elf64_Sym *sym, Elf64_Shdr *sec_hdr);
char	*epur_name(char const *str);
Elf64_Sym	*get_next_sym(Elf64_Sym *current, Elf64_Sym *last);
int	check_ar_fmt(void *data_load);
int	check_elf_fmt(unsigned char *e_ident);
void	fatal_err(char const *err_msg);
int	get_filesize(int fd);

#endif /* !MYNM_H_ */
