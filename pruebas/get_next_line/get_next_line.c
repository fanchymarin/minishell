/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:34:51 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/04/23 19:18:29 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	buf = ft_calloc(ft_strlen(memory) - i + 1, sizeof(char));
	++i;
	i2 = 0;
	while (memory[i])
		buf[i2++] = memory[i++];
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

char	*concat_str(char *buf, char *memory)
{
	char	*concat;

	concat = ft_strjoin(memory, buf);
	free(memory);
	return (concat);
}

char	*read_fd(int fd, char *memory)
{
	int		readb;
	char	*buf;

	if (!memory)
		memory = ft_calloc(1, 1);
	if (!memory)
		return (0);
	readb = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (readb > 0)
	{
		readb = read(fd, buf, BUFFER_SIZE);
		if (readb == -1)
		{
			free(buf);
			return (0);
		}
		buf[readb] = 0;
		memory = concat_str(buf, memory);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (memory);
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	memory = read_fd(fd, memory);
	if (!memory)
		return (0);
	line = return_line(memory);
	memory = save_rest(memory);
	return (line);
}
