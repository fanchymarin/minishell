/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:19:20 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/04/26 13:34:05 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
