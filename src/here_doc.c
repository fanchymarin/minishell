/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:27:23 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/04/26 14:08:50 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hdoc_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	close(STDIN_FILENO);
}

int	reading_doc(char *keyword)
{
	char	*appended_line;
	int		pip[2];
	int		stdin_cp;

	stdin_cp = dup(STDIN_FILENO);
	signal(SIGINT, &hdoc_handler);
	check_perror(pipe(pip), "pipe");
	while (1)
	{
		appended_line = readline("> ");
		if (!appended_line)
			break ;
		if (!ft_strncmp(appended_line, keyword, ft_strlen(appended_line) + 1))
			break ;
		(ft_putstr_fd(appended_line, pip[1]), ft_putchar_fd('\n', pip[1]));
		free(appended_line);
	}
	if (appended_line)
		free(appended_line);
	(close(pip[1]), dup2(stdin_cp, STDIN_FILENO), close(stdin_cp));
	return (pip[0]);
}

void	here_doc(t_cmdtable *rl, char *keyword)
{
	static int	i;
	int			heredoc_fd;

	if (i > 0)
		dup2(rl->stdfiles[STDIN_FILENO], STDIN_FILENO);
	heredoc_fd = reading_doc(keyword);
	if (rl->old_fd)
		(close(rl->old_fd), rl->old_fd = heredoc_fd);
	else
		(dup2(heredoc_fd, STDIN_FILENO), close(heredoc_fd));
	i++;
}
