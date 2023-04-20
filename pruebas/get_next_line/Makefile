NAME = get_next_line.a
FUNC = get_next_line.c get_next_line_utils.c
BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c 
OBJ = $(FUNC:.c=.o)
OBJBONUS = $(BONUS:.c=.o)
all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(OBJ): $(FUNC) 
	@gcc -c -Wall -Wextra -Werror $(FUNC)

bonus: $(OBJBONUS) $(OBJ)
	@ar rcs $(NAME) $(OBJBONUS) $(OBJ)

$(OBJBONUS): $(BONUS) 
	@gcc -c -Wall -Wextra -Werror $(BONUS)

clean:
	@rm -f *.o
fclean: clean
	@rm -f $(NAME)
re: fclean all

.PHONY: all bonus clean fclean re
