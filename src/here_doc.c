/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:27:23 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/01 19:04:42 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reading_doc(int fd_tmp, char *keyword, int control)
{
	char	*appended_line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		write(1, "> ", 3);
		appended_line = get_next_line(1);
		if (!ft_strncmp(appended_line, keyword, ft_strlen(keyword) + 1))
			break ;
		write(fd_tmp, appended_line, ft_strlen(appended_line));
		free(appended_line);
	}
	free(appended_line);
	close(fd_tmp);
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
		reading_doc(rl->fd_tmp, keyword, 0);
	(signal(SIGINT, SIG_IGN), wait(&rl->status));
	if (WTERMSIG(rl->status) == SIGINT)
		(write(STDOUT_FILENO, "\n", 1), close_fd(rl));
}
