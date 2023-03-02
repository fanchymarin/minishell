/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:19:20 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/02 20:14:00 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*nested_shell(char *line, char *keyword)
{
	(void) line;
	(void) keyword;
	return (NULL);
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
