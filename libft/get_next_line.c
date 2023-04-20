/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:21:39 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/29 21:43:58 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*save_rest(char *memory)
{
	int		i;
	int		i2;
	char	*buf;

	i = 0;
	while (memory[i] && memory[i] != '\n')
		++i;
	if (!memory[i])
	{
		free(memory);
		return (0);
	}
	buf = malloc((ft_strlen(memory) - i + 1) * sizeof(char));
	++i;
	i2 = 0;
	while (memory[i])
		buf[i2++] = memory[i++];
	buf[i2] = 0;
	free(memory);
	return (buf);
}

char	*return_line(char *buf)
{
	int		i;
	char	*p;

	i = 0;
	if (!buf[i])
		return (0);
	while (buf[i] != '\n' && buf[i])
		++i;
	p = (char *) malloc(sizeof(char) * i + 2);
	i = 0;
	while (buf[i] != '\n' && buf[i])
	{
		p[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		p[i++] = '\n';
	p[i] = 0;
	return (p);
}

char	*read_fd(int fd, char *memory)
{
	int		readb;
	char	*buf;
	char	*old_memory;

	if (!memory)
	{
		memory = malloc(sizeof(char));
		*memory = 0;
	}
	readb = 1;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (readb > 0)
	{
		readb = read(fd, buf, BUFFER_SIZE);
		if (readb == -1)
			return (free(buf), NULL);
		buf[readb] = 0;
		old_memory = memory;
		memory = ft_strjoin(old_memory, buf);
		free(old_memory);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (memory);
}

char	*select_file(int fd, t_fd_list **head)
{
	t_fd_list	*node;
	t_fd_list	*tmp;

	node = *head;
	while (node)
	{
		if (node->fd == fd)
			return (node->memory);
		tmp = node;
		node = node->next;
	}
	node = (t_fd_list *) malloc(sizeof(t_fd_list));
	*node = (t_fd_list){fd, 0, 0};
	tmp->next = node;
	return (node->memory);
}

char	*get_next_line(int fd)
{
	static t_fd_list	**head;
	char				*memory;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	if (!head)
	{
		head = (t_fd_list **) malloc(sizeof(t_fd_list *));
		*head = (t_fd_list *) malloc(sizeof(t_fd_list));
		**head = (t_fd_list){fd, 0, 0};
	}
	memory = select_file(fd, head);
	memory = read_fd(fd, memory);
	if (!memory)
		return (0);
	line = return_line(memory);
	if (!storage_memory(fd, head, save_rest(memory)))
		head = 0;
	return (line);
}
