#include "minishell.h"

char	*ft_find_path(char *cmd)
{
	int		i;
	char	**split_path;
	char	*path;

	if (!cmd)
		return (0);
	split_path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (split_path[i])
	{
		path = ft_strjoin(ft_strjoin(split_path[i], "/"), cmd);
		if (access(path, 0) == 0)
			return (path);
		i++;
	}
	free(path);
	return (0);
}

void	child_process(t_prompt *tty, int i)
{
	extern char	**environ;

	if (execve(ft_find_path(tty->cmd_lines[i][0]), tty->cmd_lines[i], environ) == -1)
		printf("bash: %s: command not found\n", tty->word[0]);
}

int	parent_process(t_prompt *tty)
{
	pid_t	pid;
	int		i;

	cmd_counter(tty);
	split_line(tty);
	i = 0;
	while (tty->n_cmd)
	{
		if ((pid = fork()) < 0)
			perror("fork");
		else if (pid == 0)
		{
			child_process(tty, i);
			return (0);
		}
		(tty->n_cmd--, i++, wait(NULL));
	}
	return (0);
}