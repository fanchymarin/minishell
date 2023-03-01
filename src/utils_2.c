/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:19:20 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/01 21:23:40 by fmarin-p         ###   ########.fr       */
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
		reading_doc(fd_tmp, keyword);
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

char	*get_next_line(int fd)
{
	char	*line;
	char	c;
	int		i;

	line = malloc(sizeof(char) * BUF_SIZE);
	if (!line)
		return (0);
	i = 0;
	while (1)
	{
		read(fd, &c, 1);
		line[i++] = c;
		if (c == '\n')
			break ;
	}
	line[i] = '\0';
	return (line);
}
