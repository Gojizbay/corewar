# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srepelli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 16:27:21 by srepelli          #+#    #+#              #
#    Updated: 2018/10/12 15:37:50 by srepelli    ###    #+. /#+    ###.fr      #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c \
	   ft_atol.c \
	   ft_isalnum.c \
	   ft_isalpha.c \
	   ft_isascii.c \
	   ft_isdigit.c \
	   ft_isnum.c \
	   ft_isprint.c \
	   ft_strcat.c \
	   ft_strchr.c \
	   ft_strcmp.c \
	   ft_strcpy.c \
	   ft_strdup.c \
	   ft_strlcat.c \
	   ft_strlen.c \
	   ft_strncat.c \
	   ft_strncpy.c \
	   ft_strnstr.c \
	   ft_strrchr.c \
	   ft_strstr.c \
	   ft_tolower.c \
	   ft_toupper.c \
	   ft_strncmp.c \
	   ft_putchar.c \
	   ft_putstr.c \
	   ft_putendl.c \
	   ft_putnbr.c \
	   ft_strsplit.c \
	   ft_strnew.c \
	   ft_strdel.c \
	   ft_strclr.c \
	   ft_memset.c \
	   ft_bzero.c \
	   ft_memccpy.c \
	   ft_memcpy.c \
	   ft_memmove.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_memalloc.c \
	   ft_itoa.c \
	   ft_memdel.c \
	   ft_striter.c \
	   ft_strmap.c \
	   ft_striteri.c \
	   ft_strmapi.c \
	   ft_strequ.c \
	   ft_strnequ.c \
	   ft_strsub.c \
	   ft_strjoin.c \
	   ft_strtrim.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_lstnew.c \
	   ft_lstdelone.c \
	   ft_lstdel.c \
	   ft_lstadd.c \
	   ft_lstiter.c \
	   ft_lstmap.c \
	   ft_power.c \
	   ft_sqrt.c \
	   ft_put_words_table.c \
	   ft_sort_int_tab.c \
	   ft_strrev.c \
	   ft_strnjoin.c \
	   ft_countchar.c \
	   ft_charpos.c \
	   get_next_line.c \
	   ft_strstrreti.c \
	   ft_arraysub.c \
	   ft_arraydup.c \
	   ft_arraynew.c \
	   ft_arraycpy.c \
	   ft_arrayissort.c \
	   ft_median.c \
	   ft_wordcount.c \
	   pf_countchar.c \
	   ft_nblen.c \
	   pf_putnbr.c \
	   ft_charpos.c \
	   ft_itoa_base.c \
	   pf_itoa.c \
	   pf_strlen.c \
	   ft_putstrn.c \
	   pf_strjoin.c \
	   ft_charstrstr.c \
	   ft_unicode.c \
	   ft_printf.c \
	   ft_precision.c \
	   ft_taille.c \
	   ft_indic.c \
	   ft_attributs.c \
	   ft_largmin.c \
	   isattrib.c \
	   indiclist1.c \
	   indiclist2.c \
	   indiclist3.c \
	   attriblist.c \
	   structure.c \
	   init_tab.c \
	   free_word_table.c

OBJ = $(SRCS:.c=.o)

HEAD = -I ./

FLAGS = -Wall -Wextra -Werror

.PHONY : all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o : %.c
	@gcc $(FLAGS) $(HEAD) -c $< -o $@

clean: 
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
