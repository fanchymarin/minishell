#include "minishell.h"

void	reading_doc(t_cmdtable *rl, char *keyword)
{
	char	*appended_line;

	while (1)
	{
		appended_line = readline(">");
		if (ft_strnstr(appended_line, keyword, ft_strlen(appended_line)))
			break;
		write(rl->pipe[1], appended_line, ft_strlen(appended_line));
		write(rl->pipe[1], "\n", 1);
		free(appended_line);
	}
	free(appended_line);
	exit(0);
}

void	here_doc(t_cmdtable *rl, char *keyword)
{
	pid_t	pid;

	if (pipe(rl->pipe) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (!pid)
		(close(rl->pipe[0]), reading_doc(rl, keyword));
	else
		(close_pipe(rl, 0), wait(NULL));
}
