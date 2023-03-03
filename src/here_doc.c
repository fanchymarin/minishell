/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:27:23 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/03 09:12:30 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reading_doc(int pipe, char *keyword, int control)
{
	char	*appended_line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		if (!control)
			ft_putstr_fd("quote", STDOUT_FILENO);
		else
			ft_putstr_fd("heredoc", STDOUT_FILENO);
		write(STDOUT_FILENO, "> ", 3);
		appended_line = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(appended_line, keyword, ft_strlen(keyword)) && control)
			break ;
		if (!control)
			ft_memset(&appended_line[ft_strlen(appended_line) - 1], 0, 1);
		write(pipe, appended_line, ft_strlen(appended_line));
		if (ft_strchr(appended_line, *keyword) && !control)
			break ;
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
		(close(rl->pipe[0]), reading_doc(rl->pipe[1], keyword, 1));
	(redirect_pipe(rl->pipe, 0), signal(SIGINT, SIG_IGN), wait(&rl->status));
	if (WTERMSIG(rl->status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}
