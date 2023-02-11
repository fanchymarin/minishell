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

void	ft_execute_cmd(t_cmdtable *rl)
{
	extern char	**environ;

	if (execve(ft_find_path(rl->cmd[0]), rl->cmd, environ) == -1)
		printf("bash: %s: command not found\n", rl->cmd[0]);
}
