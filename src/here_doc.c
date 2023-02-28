/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:27:23 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/28 15:36:13 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reading_doc(t_cmdtable *rl, char *keyword)
{
	char	*appended_line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		appended_line = readline("> ");
		if (!ft_strncmp(appended_line, keyword, ft_strlen(keyword) + 1))
			break ;
		write(rl->pipe[1], appended_line, ft_strlen(appended_line));
		write(rl->pipe[1], "\n", 1);
		free(appended_line);
	}
	close(rl->pipe[1]);
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
	close_pipe(rl, 0);
	(signal(SIGINT, SIG_IGN), wait(&rl->status));
	if (WTERMSIG(rl->status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}
