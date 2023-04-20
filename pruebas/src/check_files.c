/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:19:14 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/29 21:13:02 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_files(t_cmdtable *rl, char *file_name, char red)
{
	if ((red == LESS_THAN || red == HERE_DOC) && *file_name)
	{
		if (rl->infile)
			close(rl->infile);
		if (red == LESS_THAN)
			rl->infile = open(file_name, O_RDONLY);
		else
			here_doc(rl, file_name);
	}
	else if ((red == MORE_THAN || red == APPEND) && *file_name)
	{
		if (rl->outfile)
			close(rl->outfile);
		if (red == MORE_THAN)
			rl->outfile = open(file_name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		else
			rl->outfile = open(file_name, O_APPEND | O_CREAT | O_WRONLY, 0644);
	}
	if (rl->outfile == -1 || rl->infile == -1)
		return (ft_printf("minishell: "), perror(file_name), -1);
	else if (!*file_name)
		error_msg(red);
	return (0);
}

char	class_redirection(char *cmd_line, int i)
{
	char	red;

	red = cmd_line[i - 1];
	if (cmd_line[i] == MORE_THAN && cmd_line[i] == red)
		red = APPEND;
	else if (cmd_line[i] == LESS_THAN && cmd_line[i] == red)
		red = HERE_DOC;
	return (red);
}

int	manage_line(t_cmdtable *rl, char *cmd_line, int i)
{
	char	red;
	int		j;
	char	*name;

	j = i++;
	red = class_redirection(cmd_line, i);
	if (red == APPEND || red == HERE_DOC)
		i++;
	while (ft_isblank(cmd_line[i]))
		i++;
	ft_memmove(&cmd_line[j], &cmd_line[i], ft_strlen(cmd_line) - i + 1);
	i = i - (i - j);
	while (!ft_isblank(cmd_line[i]) && cmd_line[i]
		&& (cmd_line[i] != MORE_THAN && cmd_line[i] != LESS_THAN))
		i++;
	if (i == j)
		return (error_msg(red), -1);
	name = ft_substr(cmd_line, j, i - j);
	if (open_files(rl, name, red) == -1)
		return (free(name), -1);
	free(name);
	ft_memmove(&cmd_line[j], &cmd_line[i], ft_strlen(cmd_line) - i + 1);
	return (i = i - (i - j));
}

int	check_red_files(t_cmdtable *rl, char *cmd_line)
{
	int		i;

	i = 0;
	while (cmd_line[i])
	{
		while (cmd_line[i] == MORE_THAN || cmd_line[i] == LESS_THAN)
		{
			i = manage_line(rl, cmd_line, i);
			if (i == -1)
				return (0);
		}
		i++;
	}
	return (1);
}

char	*ft_find_path(char *cmd, t_list **env)
{
	int		i;
	char	**split_path;
	char	*path;
	char	*slashed_cmd;
	char	value_buf[BUF_SIZE];

	if (!cmd)
		return (0);
	if (!access(cmd, 0) && ft_strchr(cmd, '/'))
		return (cmd);
	split_path = ft_split(ft_getenv(env, "PATH", value_buf), ':');
	if (!split_path)
		return (0);
	i = -1;
	while (split_path[++i])
	{
		slashed_cmd = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(slashed_cmd, cmd);
		free(slashed_cmd);
		if (access(path, 0) == 0)
			return (free_dp(split_path), path);
		free(path);
	}
	free_dp(split_path);
	return (0);
}
