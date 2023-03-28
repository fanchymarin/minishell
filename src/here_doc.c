/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:27:23 by fmarin-p          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/17 13:53:26 by fmarin-p         ###   ########.fr       */
=======
/*   Updated: 2023/03/21 19:06:32 by fmarin-p         ###   ########.fr       */
>>>>>>> bd6ca7ea500eff30db8a41918f9171e6f6bae585
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reading_doc(int write_pipe, char *keyword, int control)
{
	char	*appended_line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		if (!control && ft_strncmp(keyword, "|", 1))
			ft_putstr_fd("quote", STDOUT_FILENO);
		else if (control)
			ft_putstr_fd("heredoc", STDOUT_FILENO);
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

	if (i > 0)
		check_perror(dup2(rl->std_in, 0), "dup2");
	check_perror(pipe(rl->pipe), "pipe");
	if (!check_perror(fork(), "fork"))
		(close(rl->std_in), close(rl->pipe[0]),
			reading_doc(rl->pipe[1], keyword, 1));
	(redirect_pipe(rl->pipe, 0), signal(SIGINT, SIG_IGN), wait(&rl->status));
	if (WTERMSIG(rl->status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
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
