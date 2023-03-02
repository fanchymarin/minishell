# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 14:33:11 by fmarin-p          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/03/02 15:11:55 by clcarrer         ###   ########.fr        #
=======
#    Updated: 2023/03/02 15:39:12 by fmarin-p         ###   ########.fr        #
>>>>>>> b3b7f6dc7e71d3d75a95325244452da1425aca68
#                                                                              #
# **************************************************************************** #

NAME = minishell

LDFLAGS := ${LDFLAGS}
CPPFLAGS := ${CPPFLAGS}

CFLAGS = -c -g -Wall -Wextra -Werror $(CPPFLAGS) -I$(INCDIR) -I$(LIBFTDIR) -I$(GNLDIR)
SRCFILES = main.c init_struct.c cmd.c environ_cmd.c utils.c utils_2.c \
			check_files.c pipes.c metachar_checker.c metachar_restore.c \
			vars_expansion.c here_doc.c manage_quotes.c
OBJFILES = $(SRCFILES:.c=.o)

SRCOBJ = $(addprefix $(OBJDIR), $(OBJFILES))

SRCDIR = src/
INCDIR = include/
OBJDIR = obj/
LIBFTDIR = libft/
GNLDIR = get_next_line/

all: $(NAME)

$(NAME): $(SRCOBJ)
	$(MAKE) bonus -C $(LIBFTDIR)
<<<<<<< HEAD
	gcc $^ $(LIBFTDIR)libft.a -lreadline -fsanitize=address $(LDFLAGS) -o $@
=======
	$(MAKE) bonus -C $(GNLDIR)
	gcc $^ $(LIBFTDIR)libft.a $(GNLDIR)get_next_line.a -lreadline -fsanitize=address $(LDFLAGS) -o $@
>>>>>>> b3b7f6dc7e71d3d75a95325244452da1425aca68

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p obj
	gcc -g $(CFLAGS) $^ -o $@

clean:
	$(MAKE) clean -C $(LIBFTDIR)
	$(MAKE) clean -C $(GNLDIR)
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	$(MAKE) fclean -C $(GNLDIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

#-fsanitize=address -fsanitize=leak 