/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:19:20 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/04/20 19:39:06 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*manage_pipe(char *line, int *i)
{
	(*i)++;
	while (ft_isblank(line[*i]) && line[*i])
	{
		(*i)++;
		if (line[*i] && line[*i] == PIPE)
			return (free(line), error_msg(PIPE), NULL);
	}
	if (!line[*i])
		line = nested_shell(line, "|");
	(*i)--;
	return (line);
}

int	check_perror(int code, char *name)
{
	if (code == -1)
		perror(name);
	return (code);
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
		ft_printf("minishell: syntax error near unexpected token `%c'\n", c);
	else if (c == HERE_DOC)
		ft_printf("minishell: syntax error near unexpected token `heredoc'\n");
	else if (c == APPEND)
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
}

void	redirect_pipe(int *pipe, int fd)
{
	close(pipe[fd ^ 1]);
	dup2(pipe[fd], fd);
	close(pipe[fd]);
}
