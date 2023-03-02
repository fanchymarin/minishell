/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:19:20 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/02 21:00:59 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_from_input(char *old_line, int *pipe)
{
	struct stat	pipe_inf;
	char		*new_line;
	char		*appended_line;

	if (fstat(pipe[0], &pipe_inf) == -1)
		perror("fstat");
	new_line = ft_calloc(sizeof(char),
			ft_strlen(old_line) + pipe_inf.st_size + 1);
	if (read(pipe[0], new_line, pipe_inf.st_size) == -1)
		perror("read");
	appended_line = ft_strjoin(old_line, new_line);
	(close(pipe[0]), close(pipe[1]));
	return (free(new_line), free(old_line), appended_line);
}

char	*nested_shell(char *line, char *keyword)
{
	pid_t	pid;
	int		qpipe[2];
	int		status;

	pipe(qpipe);
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (!pid)
		(close(qpipe[0]), reading_doc(qpipe[1], keyword, 0));
	(close(qpipe[1]), signal(SIGINT, SIG_IGN), wait(&status));
	if (WTERMSIG(status) == SIGINT)
		return (close(qpipe[0]), close(qpipe[1]), write(STDOUT_FILENO, "\n", 1),
			NULL);
	return (append_from_input(line, qpipe));
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

void	error_msg(char c)
{
	if (c == LESS_THAN || c == MORE_THAN || c == PIPE)
		printf("minishell: syntax error near unexpected token `%c'\n", c);
	else if (c == HERE_DOC)
	{
		c = '<';
		printf("minishell: syntax error near unexpected token `%c%c'\n", c, c);
	}
	else if (c == APPEND)
	{
		c = '>';
		printf("minishell: syntax error near unexpected token `%c%c'\n", c, c);
	}
}
