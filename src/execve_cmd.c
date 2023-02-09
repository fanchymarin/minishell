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

void	child_process(t_cmdtable *rl, int i)
{
	extern char	**environ;

	if (execve(ft_find_path(rl->cmd_lines[i][0]), rl->cmd_lines[i], environ) == -1)
		printf("bash: %s: command not found\n", rl->cmd[0]);
}

int	parent_process(t_cmdtable *rl)
{
	pid_t	pid;
	int		i;

	cmd_counter(rl);
	split_line(rl);
	i = 0;
	while (rl->n_cmd)
	{
		if ((pid = fork()) < 0)
			perror("fork");
		else if (pid == 0)
		{
			child_process(rl, i);
			return (0);
		}
		(rl->n_cmd--, i++, wait(NULL));
	}
	return (0);
}