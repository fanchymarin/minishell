/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:19:14 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/16 13:20:14 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    open_files(t_cmdtable *rl, char c, char *file_name)
{
	if (c == '<')
		rl->infile = open(file_name, O_RDONLY);
	else
		rl->outfile = open(file_name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (rl->outfile == -1 || rl->infile == -1)
		perror(file_name);
}

void	split_files(t_cmdtable *rl, char *cmd)
{
    int		i;
	char	*file_name;

	i = 1;
	while (cmd[i] && (cmd[i] != '>' && cmd[i] != '<'))
		i++;
	file_name = malloc(sizeof(char) * i);
	if (!file_name)
		perror("malloc");
	ft_strlcpy(file_name, &cmd[1], i);
	file_name = ft_strtrim(file_name, " ");
    open_files(rl, cmd[0], file_name);
	if(cmd[i])
		split_files(rl, &cmd[i]);
}

void	check_red_files(t_cmdtable *rl)
{
	int	i;
	int n;

	n = 0;
	while (rl->all_cmd[n])
	{
		i = 0;
		while (rl->all_cmd[n][i])
		{
			if (rl->all_cmd[n][i] == '<' || rl->all_cmd[n][i] == '>')
			{
				split_files(rl, &rl->all_cmd[n][i]);
				break;
			}
			i++;
		}
		n++;
	}
}