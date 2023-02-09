#include "minishell.h"

size_t	cmd_counter(t_prompt *tty)
{
	int	i;

	i = 0;
	while (tty->all_cmd[i])
		++i;
	return (i);
}

void	split_operators(t_prompt *tty)
{
    int w;
    int i;

    i = 0;
	w = 0;
    while (tty->cmd[w])
    {
        if (!ft_strncmp(tty->cmd[w], "|", 1))
        {
			tty->oper[i] = malloc(sizeof(char) * (ft_strlen(tty->cmd[w]) + 1));
			ft_memcpy(tty->oper[i], tty->cmd[w], (ft_strlen(tty->cmd[w]) + 1));
			i++;
        }
        w++;
    }
	tty->oper[i] = NULL;
}

void	last_cmd(t_prompt *tty, int i, int j, int w)
{
	int ii;

	tty->cmd_lines[i] = malloc(sizeof(char *) * (j + 1));
	ii = 0;
	while (j)
	{
		tty->cmd_lines[i][ii] = malloc(sizeof(char) * (ft_strlen(tty->cmd[w - (j-1)]) + 1));
		ft_memcpy(tty->cmd_lines[i][ii], tty->cmd[w - (j-1)], (ft_strlen(tty->cmd[w - (j-1)]) + 1));
		(j--, ii++);
	}
	tty->cmd_lines[i][ii] = NULL;
}

void	split_commands(t_prompt *tty)
{
    int w;
	int j;
    int i;
	int	ii;
    
	w = 0;
	j = 1;
	i = 0;
    while (tty->cmd[w] != NULL)
    {
        if (!ft_strncmp(tty->cmd[w], "|", 1))
        {
			j -= 1;
			tty->cmd_lines[i] = malloc(sizeof(char *) * (j + 1));
			ii = 0;
			while (j)
			{
				tty->cmd_lines[i][ii] = malloc(sizeof(char) * (ft_strlen(tty->cmd[w - j]) + 1));
				ft_memcpy(tty->cmd_lines[i][ii], tty->cmd[w - j], (ft_strlen(tty->cmd[w - j]) + 1));
				(j--, ii++);
			}
			tty->cmd_lines[i][ii] = NULL;
			i++;
        }
		if (!tty->cmd[w + 1] && ft_strncmp(tty->cmd[w], "|", 1))
			last_cmd(tty, i, j, w);
		j++;
        w++;
    }
}

void	split_line(t_prompt *tty)
{
	cmd_counter(tty);
    tty->cmd_lines = malloc(sizeof(char **) * (tty->n_cmd + 1));
	tty->oper = malloc(sizeof(char *) * (tty->n_oper + 1));
    if (!tty->cmd_lines || !tty->oper)
        perror("malloc");
	split_operators(tty);
	split_commands(tty);
}