# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fherbine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 17:03:11 by fherbine          #+#    #+#              #
#    Updated: 2018/09/08 04:12:01 by fherbine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBSH = libsh/
OBJ_PATH = ./debug
SRCS = ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c \
	   ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
	   ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
	   ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	   ft_isdigit.c ft_isprint.c ft_tolower.c ft_toupper.c ft_bzero.c \
	   ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	   ft_memset.c ft_memalloc.c ft_memdel.c ft_strclr.c ft_strdel.c \
	   ft_striter.c ft_strnew.c ft_striteri.c ft_strmap.c ft_strmapi.c \
	   ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
	   ft_itoa.c ft_strsplit.c ft_putchar.c ft_putstr.c ft_putendl.c \
	   ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	   ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
	   ft_lstiter.c ft_lstmap.c ft_swap.c ft_str_is_printable.c \
	   ft_putnbr_base.c get_next_line.c ft_absol.c ft_nlen_base.c ft_nlen.c \
	   ft_itoa_base.c ft_prints.c ft_specifier_prints.c ft_put_n_char.c \
	   ft_append_slash.c ft_is_in_dir.c ft_tab_len.c ft_free_tab.c \
	   ft_tab_del_elem.c ft_copy_tab.c ft_add_tab_elem.c ft_capitalize.c \
	   ft_strinarray.c ft_sqrt.c $(LIBSH)/ft_getenv.c
NAME = libft.a
INCLUDES = ./
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I $(INCLUDES)
OBJ_NAME = $(SRCS:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
CC = gcc

all: $(NAME)

$(OBJ_PATH):
	@mkdir $@
	@mkdir $@/$(LIBSH)

$(NAME): $(OBJ_PATH) $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "✅ Source files: 81 / 81\033[0m --> \033[1;32m[Done]\033[0m"

$(OBJ_PATH)/%.o: %.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $? -o $@
	@echo "🔧 Source files: $(shell ls -1 $(OBJ_PATH) | wc -l) / 81\r\c"

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
