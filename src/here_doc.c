/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:27:23 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/04/25 13:53:39 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reading_doc(char *keyword, int control)
{
	char	*appended_line;
	int		pip[2];

	check_perror(pipe(pip), "pipe");
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		appended_line = get_next_line(STDIN_FILENO);
		if (control && !ft_strncmp(appended_line, keyword,
				ft_strlen(appended_line + 1)))
			break ;
		if (!control)
			ft_memset(&appended_line[ft_strlen(appended_line) - 1], 0, 1);
		ft_putstr_fd(appended_line, pip[1]);
		if (!control && (ft_strchr(appended_line, *keyword) || *keyword == '|'))
			break ;
		free(appended_line);
	}
	free(appended_line);
	close(pip[1]);
	return (pip[0]);
}

void	here_doc(t_cmdtable *rl, char *keyword)
{
	static int	i;
	int			heredoc_fd;

	if (i > 0)
		dup2(rl->stdfiles[STDIN_FILENO], STDIN_FILENO);
	check_perror(pipe(rl->pipe), "pipe");
	heredoc_fd = reading_doc(keyword, 1);
	if (rl->old_fd)
		(close(rl->old_fd), rl->old_fd = heredoc_fd);
	else
		(dup2(heredoc_fd, STDIN_FILENO), close(heredoc_fd));
	i++;
}

char	*append_from_input(char *old_line, int fd)
{
	char		*new_line;
	char		*appended_line;

	new_line = ft_calloc(sizeof(char), BUF_SIZE);
	check_perror(read(fd, new_line, BUF_SIZE), "read");
	appended_line = ft_strjoin(old_line, new_line);
	check_perror(close(fd), "close");
	if (!*new_line)
		return (free(new_line), free(old_line),
			ft_putchar_fd('\n', STDOUT_FILENO), NULL);
	return (free(new_line), free(old_line), appended_line);
}
