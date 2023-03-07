# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 14:15:33 by fmarin-p          #+#    #+#              #
#    Updated: 2023/03/07 16:51:05 by fmarin-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCFILES = ft_printchar.c ft_printhex.c ft_printpt.c ft_printuns.c ft_printf.c ft_printnbr.c ft_printstr.c
HDRFILES = ft_printf.h libft.h

SRCDIR = src/
OBJDIR = obj/
HDRDIR = include

SRC = $(addprefix $(SRCDIR), $(SRCFILES))
HDR = $(addprefix $(HDRDIR), $(HDRFILES))

SRCOBJ = $(addprefix $(OBJDIR), $(SRCFILES:.c=.o))

CFLAGS = -Wall -Wextra -Werror -I

all: $(NAME)

$(NAME): $(SRCOBJ)
	@$(MAKE) -C libft
	@cp libft/libft.a .
	@mv libft.a $(NAME)
	@ar rcs $(NAME) $(SRCOBJ)

$(OBJDIR)%.o: $(SRCDIR)%.c	
	@mkdir -p obj
	@gcc -c $(CFLAGS) $(HDRDIR) $< -o $@

clean:
	@$(MAKE) clean -C libft
	@rm -rf $(OBJDIR)

fclean: clean
	@$(MAKE) fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
