/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:27:23 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/28 16:25:08 by fmarin-p         ###   ########.fr       */
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
		write(rl->fd_tmp, appended_line, ft_strlen(appended_line));
		write(rl->fd_tmp, "\n", 1);
		free(appended_line);
	}
	free(appended_line);
	close(rl->fd_tmp);
	exit(0);
}

void	here_doc(t_cmdtable *rl, char *keyword)
{
	pid_t	pid;

	rl->fd_tmp = open(".tmp", O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (rl->fd_tmp == -1)
		perror("open");
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (!pid)
		reading_doc(rl, keyword);
	(signal(SIGINT, SIG_IGN), wait(&rl->status));
	if (WTERMSIG(rl->status) == SIGINT)
		(write(STDOUT_FILENO, "\n", 1), close_fd(rl));
}
