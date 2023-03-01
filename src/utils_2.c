/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:19:20 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/01 16:00:38 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_from_file(char *line)
{
	int			fd_tmp;
	char		*app_line;
	char		*new_line;
	struct stat	file;

	fd_tmp = open(".tmp", O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (fd_tmp == -1)
		perror("open");
	stat(".tmp", &file);
	app_line = ft_calloc(sizeof(char), file.st_size);
	read(fd_tmp, app_line, file.st_size);
	new_line = ft_strjoin(line, app_line);
	free(line);
	free(app_line);
	close(fd_tmp);
	return (new_line);
}

char	*nested_shell(char *line, char *keyword)
{
	pid_t	pid;
	int		fd_tmp;
	int		status;

	fd_tmp = open(".tmp", O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (fd_tmp == -1)
		perror("open");
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (!pid)
		reading_doc(fd_tmp, keyword, 1);
	(signal(SIGINT, SIG_IGN), wait(&status));
	if (WTERMSIG(status) == SIGINT)
		return (write(STDOUT_FILENO, "\n", 1), NULL);
	return (append_from_file(line));
}

void	ft_lstdelnode(t_list **head, t_list *node, t_list *tmp)
{
	if (node == *head)
		*head = node->next;
	else
		tmp->next = node->next;
	free(node->content);
	free(node);
	if (!*head)
		free(head);
}

int	quotes_closed(char *line, int i, char quote)
{
	int	quotes_counter;
	int	last_quote;

	quotes_counter = 0;
	last_quote = 0;
	while (line[i])
	{
		if (line[i] == quote)
		{
			last_quote = i;
			quotes_counter++;
		}
		i++;
	}
	if (quotes_counter % 2 == 0)
		return (last_quote);
	return (-1);
}

void	close_fd(t_cmdtable *rl)
{
	pid_t	pid;
	char	**cmd;

	rl->infile = 0;
	rl->outfile = 0;
	if (rl->fd_tmp)
	{
		(close(rl->fd_tmp), rl->fd_tmp = 0);
		cmd = ft_split("rm -f .tmp", ' ');
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (!pid)
		{
			execve_cmd(rl->env, ft_find_path(cmd[0], rl->env), cmd);
			exit(0);
		}
		free_dp(cmd);
	}
}
