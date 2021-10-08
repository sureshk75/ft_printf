# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/10 17:31:06 by schetty           #+#    #+#              #
#    Updated: 2021/10/02 23:19:55 by schetty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and Linker
CC			:=	gcc

# Target Binary Program
NAME		:=	libftprintf.a

# Directories
OBJDIR		:=	obj/
LIBFTDIR	:=	libft/

# Flags, Libraries and Includes
CFLAGS		:=	-Wall -Wextra -Werror

# Functions
ARCHIVE		:=	ar rc
INDEXER		:=	ranlib
DELETE		:=	rm -f
CREATEDIR	:=	mkdir -p
DELETEDIR	:=	rm -Rf

# Colors
GRN			:=	"\033[1;32m"
RED			:=	"\033[1;31m"
YLW			:=	"\033[1;33m"
CLR			:=	"\033[0m"

# Source, Objects and Resources
SOURCES		:=	ft_printf.c		ft_printf_parser.c	ft_printf_utils.c
OBJECTS		:=	$(patsubst %,$(OBJDIR)%,$(SOURCES:.c=.o))
LIBFTOBJ	:=	$(LIBFTDIR)/obj/*.o

# Defauilt Make
all			:	outdir $(NAME)
				@ echo $(GRN)$(basename $(NAME))$(CLR) Generated Successfully!

outdir		:
				@ $(CREATEDIR) $(OBJDIR)

bonus		:	outdir $(NAME)
				@ echo $(GRN)$(basename $(NAME))$(CLR) Generated Successfully!

# Link
$(NAME)		:	$(OBJECTS)
				@ $(MAKE) -C $(LIBFTDIR) --no-print-directory
				@ $(ARCHIVE) $(NAME) $(OBJECTS) $(LIBFTOBJ)
				@ $(INDEXER) $(NAME)

# Compile
$(OBJDIR)%.o:	%.c
				@ $(CC) $(CFLAGS) -c $< -o $@

# Clean Objects
clean		:
ifneq ($(wildcard $(OBJDIR)*.o),)
	@ $(MAKE) clean -C $(LIBFTDIR) --no-print-directory
	@ $(DELETE) $(OBJECTS)
	@ $(DELETEDIR) $(OBJDIR)
	@ echo $(YLW)$(basename $(NAME))$(CLR) Object Files Deleted!
else
	@ echo No $(RED)$(basename $(NAME))$(CLR) Object Files To Remove..
endif

# Full Clean
fclean		:
ifneq ($(wildcard $(NAME)),)
	@ $(MAKE) fclean -C $(LIBFTDIR) --no-print-directory
	@ $(DELETE) $(NAME)
	@ $(DELETE) $(OBJECTS)
	@ $(DELETEDIR) $(OBJDIR)
	@ echo $(YLW)$(basename $(NAME))$(CLR) Binary \& Object Files Deleted!
else
	@ echo No $(RED)$(basename $(NAME))$(CLR) Binary Or Object Files To Removed..
endif

# Recompile
re			:	fclean all

# Non-File Targets
.PHONY		:	all clean fclean re bonus
