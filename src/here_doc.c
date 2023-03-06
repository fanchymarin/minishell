/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:27:23 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/03 10:13:01 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reading_doc(int write_pipe, char *keyword, int control)
{
	char	*appended_line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		if (!control && !ft_strncmp(keyword, "|\n", 2))
			ft_putstr_fd("quote", STDOUT_FILENO);
		else if (control)
			ft_putstr_fd("heredoc", STDOUT_FILENO);
		ft_putstr_fd("> ", STDOUT_FILENO);
		appended_line = get_next_line(STDIN_FILENO);
		if (control &&!ft_strncmp(appended_line, keyword, ft_strlen(keyword)))
			break ;
		if (!control)
			ft_memset(&appended_line[ft_strlen(appended_line) - 1], 0, 1);
		ft_putstr_fd(appended_line, write_pipe);
		if (!control && (ft_strchr(appended_line, *keyword) ||
			ft_strncmp(keyword, "|\n", 2)))
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
	char		*new_line;
	char		*appended_line;

	new_line = ft_calloc(sizeof(char), BUF_SIZE);
	err(read(read_pipe, new_line, BUF_SIZE), "read");
	appended_line = ft_strjoin(old_line, new_line);
	err(close(read_pipe), "close");
	return (free(new_line), free(old_line), appended_line);
}

char	*nested_shell(char *line, char *keyword)
{
	int		qpipe[2];
	int		status;

	err(pipe(qpipe), "pipe");
	if (!err(fork(), "fork"))
		(err(close(qpipe[0]), "close"), reading_doc(qpipe[1], keyword, 0));
	(err(close(qpipe[1]), "close"), signal(SIGINT, SIG_IGN), wait(&status));
	if (WTERMSIG(status) == SIGINT)
		return (close(qpipe[0]), write(STDOUT_FILENO, "\n", 1),
			NULL);
	return (append_from_input(line, qpipe[0]));
}
