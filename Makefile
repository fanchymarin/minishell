# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 14:33:11 by fmarin-p          #+#    #+#              #
#    Updated: 2023/03/29 22:11:32 by fmarin-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LDFLAGS := ${LDFLAGS}
CPPFLAGS := ${CPPFLAGS}

CFLAGS = -Wall -Wextra -Werror $(CPPFLAGS) -I$(INCDIR) -I$(LIBFTDIR) -I$(PRINTFDIR)include/
SRCFILES = main.c init_struct.c cmd.c environ_cmd.c utils.c utils_2.c \
			check_files.c pipes.c metachar_checker.c metachar_restore.c \
			vars_expansion.c here_doc.c check_syntax_export.c 
OBJFILES = $(SRCFILES:.c=.o)

SRCOBJ = $(addprefix $(OBJDIR), $(OBJFILES))

SRCDIR = src/
INCDIR = include/
OBJDIR = obj/
LIBFTDIR = libft/
PRINTFDIR = ft_printf/

all: $(NAME)

debug: CFLAGS += -g
debug: $(NAME)

$(NAME): $(SRCOBJ)
	$(MAKE) bonus -C $(LIBFTDIR)
	$(MAKE) -C $(PRINTFDIR)
	gcc $^ $(LIBFTDIR)libft.a $(PRINTFDIR)libftprintf.a -lreadline $(LDFLAGS) -o $@

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p obj
	gcc -c $(CFLAGS) $^ -o $@

clean:
	$(MAKE) clean -C $(LIBFTDIR)
	$(MAKE) clean -C $(PRINTFDIR)
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	$(MAKE) fclean -C $(PRINTFDIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
