/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:19:20 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/04 19:01:00 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_dp(char **dp)
{
	int	i;

	i = -1;
	while (dp[++i])
		printf("dp[%d]:_%s_\n", i, dp[i]);
}

char	**restore_equals(char **var)
{
	int		i;
	char	*old_value;

	i = 1;
	while (var[++i])
	{
		old_value = var[1];
		var[1] = ft_strjoin(var[1], var[i]);
		free(old_value);
	}
	return (var);
}