/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:27:23 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/03 09:44:32 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reading_doc(int write_pipe, char *keyword, int control)
{
	char	*appended_line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		if (!control)
			ft_putstr_fd("quote", STDOUT_FILENO);
		else
			ft_putstr_fd("heredoc", STDOUT_FILENO);
		ft_putstr_fd("> ", STDOUT_FILENO);
		appended_line = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(appended_line, keyword, ft_strlen(keyword)) && control)
			break ;
		if (!control)
			ft_memset(&appended_line[ft_strlen(appended_line) - 1], 0, 1);
		ft_putstr_fd(appended_line, write_pipe);
		if (ft_strchr(appended_line, *keyword) && !control)
			break ;
		free(appended_line);
	}
	free(appended_line);
	close(write_pipe);
	exit(0);
}

void	here_doc(t_cmdtable *rl, char *keyword)
{
	err(pipe(rl->pipe), "pipe");
	if (!err(fork(), "fork"))
		(close(rl->pipe[0]), reading_doc(rl->pipe[1], keyword, 1));
	(redirect_pipe(rl->pipe, 0), signal(SIGINT, SIG_IGN), wait(&rl->status));
	if (WTERMSIG(rl->status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}

char	*append_from_input(char *old_line, int read_pipe)
{
	struct stat	pipe_inf;
	char		*new_line;
	char		*appended_line;

	err(fstat(read_pipe, &pipe_inf), "fstat");
	new_line = ft_calloc(sizeof(char),
			ft_strlen(old_line) + pipe_inf.st_size + 1);
	err(read(read_pipe, new_line, pipe_inf.st_size), "read");
	appended_line = ft_strjoin(old_line, new_line);
	close(read_pipe);
	printf("old_line:_%s_\nnew_line:_%s_\napp_line:_%s_\n", old_line, new_line, appended_line);
	return (free(new_line), free(old_line), appended_line);
}

char	*nested_shell(char *line, char *keyword)
{
	pid_t	pid;
	int		qpipe[2];
	int		status;

	err(pipe(qpipe), "pipe");
	if (!err(fork(), "fork"))
		(close(qpipe[0]), reading_doc(qpipe[1], keyword, 0));
	(err(close(qpipe[1]), "close"), signal(SIGINT, SIG_IGN), wait(&status));
	if (WTERMSIG(status) == SIGINT)
		return (close(qpipe[0]), write(STDOUT_FILENO, "\n", 1),
			NULL);
	return (append_from_input(line, qpipe[0]));
}
