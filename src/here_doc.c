/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:27:23 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/01 21:09:08 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_cmdtable *rl)
{
	rl->infile = 0;
	rl->outfile = 0;
	close(rl->pipe[0]);
	close(rl->pipe[1]);
}

void	reading_doc(int pipe, char *keyword)
{
	char	*appended_line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		write(1, "> ", 3);
		appended_line = get_next_line(1);
		if (!ft_strncmp(appended_line, keyword, ft_strlen(keyword)))
			break ;
		write(pipe, appended_line, ft_strlen(appended_line));
		free(appended_line);
	}
	free(appended_line);
	close(pipe);
	exit(0);
}

void	here_doc(t_cmdtable *rl, char *keyword)
{
	pid_t	pid;

	pipe(rl->pipe);
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (!pid)
		(close(rl->pipe[0]), reading_doc(rl->pipe[1], keyword));
	else
		(close_pipe(rl, 0), wait(&rl->status));
	(signal(SIGINT, SIG_IGN), wait(&rl->status));
	if (WTERMSIG(rl->status) == SIGINT)
		(write(STDOUT_FILENO, "\n", 1), close_fd(rl));
}
