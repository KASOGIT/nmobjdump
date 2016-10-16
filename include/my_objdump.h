/*
** my_objdump.h for  in /home/soto_a/test/test
** 
** Made by adam soto
** Login   <soto_a@epitech.net>
** 
** Started on  Mon Feb 22 16:40:12 2016 adam soto
** Last update Sun Feb 28 21:13:12 2016 
*/

#ifndef MYOBJDUMP_H_
#define MYOBJDUMP_H_

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

typedef struct	s_flags
{
  int		flag;
  char		*name;
}		t_flags;

extern int	g_size;
extern char	*g_file_path;

void	err_ar();
int	err_trunc();
int	check_fmt_addr(Elf64_Shdr *sec_hdr, int i);
int	check_truncated(void *data_load, Elf64_Ehdr *elf_hdr,
			Elf64_Shdr *sec_hdr);
int	get_filesize(int fd);
void	fatal_err(char const *err_msg);
int	check_elf_fmt(unsigned char *e_ident);
char	*get_file_fmt(unsigned char *e_ident);
char	*get_flag(uint16_t e_type);
char	*get_flags_enum(uint16_t e_type);
int	get_flags(Elf64_Ehdr *elf_hdr, Elf64_Shdr *sec_hdr);
void	show_flags(int flags);
void	display_hdr_info(char const *file_path, Elf64_Ehdr *elf_hdr,
			 Elf64_Shdr *sec_hdr);
void	display_char_readable(unsigned char *sub, int count);
int	format_and_display(int start, int max, unsigned char *mem);
int	is_displayable(char *sec_name);
void	fmt_sec_and_display(Elf64_Shdr *sec_hdr, char *strtab,
			    void *data_load, int i);
void	display_section_data(Elf64_Shdr *sec_hdr, char *strtab,
			     void *data_load, Elf64_Ehdr *elf_hdr);
int	check_elf_fmt(unsigned char *e_ident);
char	*get_file_fmt(unsigned char *e_ident);
char	*get_flag(uint16_t e_type);
char	*get_flags_enum(uint16_t e_type);
int	check_ar_fmt(void *data_load);
void	get_elf_data_and_act(void *data_load, Elf64_Ehdr *elf_hdr,
			     char const *file_path);
char	*get_elf_name(char *name, char *s_tab_name);
void	act_data_ar(void *ptr, char *name, int i, char *s_tab_name);
void	parse_ar_file_and_act(void *data_load, int fd);
void	my_objdump(int fd);

#endif /* !MYOBJDUMP_H_ */
