/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:19:14 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/23 15:09:15 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_files(t_cmdtable *rl, char *file_name, int d)
{
	// if (c == LESS_THAN)
	// {
	// 	if (rl->infile)
	// 		close(rl->infile);
	// 	rl->infile = open(file_name, O_RDONLY);
	// }
	if (rl->outfile)
		close(rl->outfile);
	if (d == 0)
		rl->outfile = open(file_name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	else if (d == 1)
		rl->outfile = open(file_name, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (rl->outfile == -1)
		perror(file_name);
}

void	check_red_files(t_cmdtable *rl, char *cmd_line)
{
	int		i;
	int		j;
	int		d;

	i = 0;
	while (cmd_line[i])
	{
		rl->outfile = 0;
		while (cmd_line[i] == MORE_THAN)
		{
			j = i++;
			d = 0;
			if (cmd_line[i] == MORE_THAN)
				d = 1;
			if (d)
				i++;
			while (ft_isblank(cmd_line[i]))
				i++;
			ft_memmove(&cmd_line[j], &cmd_line[i], ft_strlen(cmd_line) - i + 1);
			i = i - (i - j);
			while (!ft_isblank(cmd_line[i]) && cmd_line[i] && cmd_line[i] != MORE_THAN)
				i++;
			open_files(rl, ft_substr(cmd_line, j, i - j), d);
			ft_memmove(&cmd_line[j], &cmd_line[i], ft_strlen(cmd_line) - i + 1);
			i = i - (i - j);
		}
		i++;
	}
}
