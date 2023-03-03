/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:16:44 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/03 10:26:30 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	storage_memory(int fd, t_list **head, char *memory)
{
	t_list	*node;
	t_list	*tmp;

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

char	*ft_strchr_gnl(const char *s, int c)
{
	char	*p;

	if (c > 255)
		c -= 256;
	while (*s)
	{
		if (*s == c)
		{
			p = (char *)s;
			return (p);
		}
		s++;
	}
	if (c == 0)
	{
		p = (char *)s;
		return (p);
	}
	return (0);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*p;
	int		i;

	if (!s1 || !s2)
		return (0);
	p = (char *) malloc
		(sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2)) + 1);
	if (!p)
		return (0);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		++i;
	}
	while (*s2)
		p[i++] = *(s2++);
	p[i] = 0;
	free((char *)s1);
	return (p);
}

size_t	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

int	free_list(t_list **head, t_list *node, t_list *tmp)
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
