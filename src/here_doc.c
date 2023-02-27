#include "minishell.h"

void	reading_doc(t_cmdtable *rl, char *keyword)
{
	char	*appended_line;

	while (1)
	{
		appended_line = readline(">");
		if (ft_strnstr(appended_line, keyword, ft_strlen(appended_line)))
			break;
		write(rl->aux_file, appended_line, ft_strlen(appended_line));
		write(rl->aux_file, "\n", 1);
		free(appended_line);
	}
	free(appended_line);
}

void	here_doc(t_cmdtable *rl, char *keyword)
{
	pid_t	pid;

	rl->aux_file = open("aux", O_APPEND | O_CREAT | O_RDWR, 0644);
	pid = fork();
	if (!pid)
	{
		reading_doc(rl, keyword);
		exit(0);
	}
	else
		wait(NULL);
}
