/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:19:14 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/23 16:50:07 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_files(t_cmdtable *rl, char *file_name, char red)
{
	if (red == LESS_THAN || red == HERE_DOC)
	{
		if (rl->infile)
			close(rl->infile);
		if (red == LESS_THAN)
			rl->infile = open(file_name, O_RDONLY);
	}
	if (red == MORE_THAN || red == APPEND)
	{
		if (rl->outfile)
			close(rl->outfile);
		if (red == MORE_THAN)
			rl->outfile = open(file_name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		else
			rl->outfile = open(file_name, O_APPEND | O_CREAT | O_WRONLY, 0644);
	}
	if (rl->outfile == -1)
		perror(file_name);
}

int	manage_line(t_cmdtable *rl, char *cmd_line, int i)
{
	char	red;
	int		j;

	j = i++;
	red = cmd_line[i - 1];
	if (cmd_line[i] == MORE_THAN)
		red = APPEND;
	else if (cmd_line[i] == LESS_THAN)
		red = HERE_DOC;
	if (red == APPEND || red == HERE_DOC)
		i++;
	while (ft_isblank(cmd_line[i]))
		i++;
	ft_memmove(&cmd_line[j], &cmd_line[i], ft_strlen(cmd_line) - i + 1);
	i = i - (i - j);
	while (!ft_isblank(cmd_line[i]) && cmd_line[i]
		&& (cmd_line[i] != MORE_THAN && cmd_line[i] != LESS_THAN))
		i++;
	open_files(rl, ft_substr(cmd_line, j, i - j), red);
	ft_memmove(&cmd_line[j], &cmd_line[i], ft_strlen(cmd_line) - i + 1);
	i = i - (i - j);
	return (i);
}

void	check_red_files(t_cmdtable *rl, char *cmd_line)
{
	int		i;

	i = 0;
	while (cmd_line[i])
	{
		while (cmd_line[i] == MORE_THAN || cmd_line[i] == LESS_THAN)
			i = manage_line(rl, cmd_line, i);
		i++;
	}
}
