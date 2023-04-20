/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:27:23 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/28 18:24:08 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reading_doc(int write_pipe, char *keyword, int control)
{
	char	*appended_line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		appended_line = get_next_line(STDIN_FILENO);
		if (control && !ft_strncmp(appended_line, keyword,
				ft_strlen(appended_line + 1)))
			break ;
		if (!control)
			ft_memset(&appended_line[ft_strlen(appended_line) - 1], 0, 1);
		ft_putstr_fd(appended_line, write_pipe);
		if (!control && (ft_strchr(appended_line, *keyword) || *keyword == '|'))
			break ;
		free(appended_line);
	}
	free(appended_line);
	close(write_pipe);
	exit(0);
}

void	here_doc(t_cmdtable *rl, char *keyword)
{
	static int	i;
	int	p[2];

	if (i > 0)
		check_perror(dup2(rl->std_in, 0), "dup2");
	check_perror(pipe(p), "pipe");
	if (!check_perror(fork(), "fork"))
		(close(p[0]), reading_doc(p[1], keyword, 1));
	check_perror(rl->std_in = dup(0), "dup");
	(dup2(0, p[0]), close(p[1]), signal(SIGINT, SIG_IGN), wait(&rl->status));
	if (WTERMSIG(rl->status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	(dup2(rl->std_in, 0), close(rl->std_in));
	i++;
}

char	*append_from_input(char *old_line, int read_pipe)
{
	char		*new_line;
	char		*appended_line;

	new_line = ft_calloc(sizeof(char), BUF_SIZE);
	check_perror(read(read_pipe, new_line, BUF_SIZE), "read");
	appended_line = ft_strjoin(old_line, new_line);
	check_perror(close(read_pipe), "close");
	if (!*new_line)
		return (free(new_line), free(old_line),
			ft_putchar_fd('\n', STDOUT_FILENO), NULL);
	return (free(new_line), free(old_line), appended_line);
}

char	*nested_shell(char *line, char *keyword)
{
	int		qpipe[2];
	int		status;

	check_perror(pipe(qpipe), "pipe");
	if (!check_perror(fork(), "fork"))
		(check_perror(close(qpipe[0]), "close"),
			reading_doc(qpipe[1], keyword, 0));
	(check_perror(close(qpipe[1]), "close"), signal(SIGINT, SIG_IGN),
		wait(&status));
	if (WTERMSIG(status) == SIGINT)
		return (close(qpipe[0]), write(STDOUT_FILENO, "\n", 1),
			NULL);
	return (append_from_input(line, qpipe[0]));
}