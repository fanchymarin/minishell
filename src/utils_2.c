/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:19:20 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/05 18:48:24 by fmarin-p         ###   ########.fr       */
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
			return (error_msg(PIPE), NULL);
	}
	if (!line[*i])
		line = nested_shell(line, "|");
	(*i)--;
	return (line);
}

int	err(int code, char *name)
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
		printf("minishell: syntax error near unexpected token `%c'\n", c);
	else if (c == HERE_DOC)
		printf("minishell: syntax error near unexpected token `heredoc'\n");
	else if (c == APPEND)
		printf("minishell: syntax error near unexpected token `newline'\n");
}

void	print_dp(char **dp)
{
	int	i;

	i = -1;
	while (dp[++i])
		printf("dp[%d]:_%s_\n", i, dp[i]);
}
