/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:16:44 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/29 21:49:35 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	storage_memory(int fd, t_fd_list **head, char *memory)
{
	t_fd_list	*node;
	t_fd_list	*tmp;

	node = *head;
	tmp = node;
	while (node)
	{
		if (node->fd == fd)
		{
			if (!memory)
			{
				if (!free_list(head, node, tmp))
					return (0);
			}
			else
				node->memory = memory;
			break ;
		}
		tmp = node;
		node = node->next;
	}
	return (1);
}

int	free_list(t_fd_list **head, t_fd_list *node, t_fd_list *tmp)
{
	if (node == *head)
		*head = node->next;
	else
		tmp->next = node->next;
	free(node);
	if (!*head)
	{
		free(head);
		return (0);
	}
	return (1);
}
