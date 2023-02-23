/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:19:14 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/23 10:45:00 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_files(t_cmdtable *rl, char c, char *file_name, int n)
{
	if (c == LESS_THAN && rl->infile == 0)
		rl->infile = open(file_name, O_RDONLY);
	// else if (c == 'H')
	// 	here_docs()
	else if (c == MORE_THAN && rl->outfile[n] == 0)
		rl->outfile[n] = open(file_name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	else if (c == 'A' && rl->outfile[n] == 0)
		rl->outfile[n] = open(file_name, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (rl->outfile[n] == -1 || rl->infile == -1)
		perror(file_name);
}

char	class_redirection(char *cmd)
{
	char	red;

	red = cmd[0];
	if (cmd[0] == MORE_THAN && cmd[1] == MORE_THAN)
		(red = 'A');
	else if (cmd[0] == LESS_THAN && cmd[1] == LESS_THAN)
		red = 'H';
	return (red);
}

void	split_files(t_cmdtable *rl, char *cmd, int n)
{
	int		i;
	int		start;
	char	red;
	char	*file;

	i = 1;
	red = class_redirection(cmd);
	if (red == 'A' || red == 'H')
		i++;
	start = i;
	while (cmd[i] && (cmd[i] != MORE_THAN && cmd[i] != LESS_THAN))
		i++;
	file = malloc(sizeof(char) * i - start);
	if (!file)
		perror("malloc");
	ft_strlcpy(file, &cmd[start], (i - start + 1));
	file = ft_strtrim(file, " ");
	cmd = ft_substr(cmd, i, ft_strlen(cmd) - i);
	open_files(rl, red, file, n);
	free(file);
	if (cmd[0] == MORE_THAN || cmd[0] == LESS_THAN)
		split_files(rl, cmd, n);
}

void	check_red_files(t_cmdtable *rl)
{
	int	i;
	int	n;

	rl->outfile = malloc(sizeof(int) * rl->n_cmd);
	if (!rl->outfile)
		perror("malloc");
	n = 0;
	while (rl->all_cmd[n])
	{
		i = 0;
		while (rl->all_cmd[n][i])
		{
			if (rl->all_cmd[n][i] == '<' || rl->all_cmd[n][i] == '>')
			{
				rl->outfile[n] = 0;
				split_files(rl, &rl->all_cmd[n][i], n);
				rl->all_cmd[n] = ft_substr(rl->all_cmd[n], 0, i);
				rl->all_cmd[n] = ft_strtrim(rl->all_cmd[n], " ");
				break ;
			}
			i++;
		}
		n++;
	}
}
