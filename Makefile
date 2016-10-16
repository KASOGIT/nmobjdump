##
## Makefile for  in /home/soto_a/test/test
## 
## Made by adam soto
## Login   <soto_a@epitech.net>
## 
## Started on  Thu Feb 25 21:49:35 2016 adam soto
## Last update Sun Oct 16 23:23:50 2016 
##

NM		=	my_nm
OBJDUMP		=	my_objdump

SRC_OBJ		=	src_obj/ar_mngt.c		\
			src_obj/fmt_display.c		\
			src_obj/header.c		\
			src_obj/my_objdump.c		\
			src_obj/utils_obj.c		\
			src_obj/obj_main.c		\
			src_obj/flags_mngt.c		\

SRC_NM		=	src_nm/nm_main.c		\
			src_nm/my_nm.c			\
			src_nm/ar_mngt.c		\
			src_nm/fill_tab.c		\
			src_nm/display_tab.c		\
			src_nm/get_flags.c		\
			src_nm/sort_tab.c		\
			src_nm/nm_utils.c		\

NM_OBJ		=	$(SRC_NM:.c=.o)

OD_OBJ		=	$(SRC_OBJ:.c=.o)

INCLUDES	=	-I./include
CFLAGS		=	$(INCLUDES) -O2 -pipe

CC		=	gcc
RM		=	rm -rf

all		:
			make $(OBJDUMP)
			make $(NM)

objdump		:	
			make $(OBJDUMP)

nm		:	
			make $(NM)

$(NM)		:	$(NM_OBJ)
			$(CC) $(NM_OBJ) -o $(NM)

$(OBJDUMP)	:	$(OD_OBJ)
			$(CC) $(OD_OBJ) -o $(OBJDUMP)

clean		:
			$(RM) $(NM_OBJ)
			$(RM) $(OD_OBJ)

fclean		:	clean
			$(RM) $(NM)
			$(RM) $(OBJDUMP)

re		:	fclean all

.PHONY		:	all clean fclean re
