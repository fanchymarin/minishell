# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmarin-p <fmarin-p@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 14:33:11 by fmarin-p          #+#    #+#              #
#    Updated: 2023/02/09 18:01:04 by fmarin-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -c -g -Wall -Wextra -Werror -I$(INCDIR) -I$(LIBFTDIR)  

SRCFILES = main.c cmd.c export_cmd.c utils.c execve_cmd.c split_cmd.c
OBJFILES = $(SRCFILES:.c=.o)

SRCOBJ = $(addprefix $(OBJDIR), $(OBJFILES))

SRCDIR = src/
INCDIR = include/
OBJDIR = obj/
LIBFTDIR = libft/

all: $(NAME)

$(NAME): $(SRCOBJ)
	$(MAKE) bonus -C $(LIBFTDIR)
	gcc $^ $(LIBFTDIR)libft.a -lreadline -o $@

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p obj
	gcc $(CFLAGS) $^ -o $@

clean:
	$(MAKE) clean -C $(LIBFTDIR)
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
