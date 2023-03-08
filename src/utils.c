/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:55:15 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/08 15:43:54 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_cmdtable *rl)
{
	if (rl->infile)
		(close(rl->infile), rl->infile = 0);
	if (rl->outfile)
		(close(rl->outfile), rl->outfile = 0);
}

void	free_dp(char **dp)
{
	int	i;

	i = 0;
	while (dp[i])
		free(dp[i++]);
	free(dp);
}

char	*ft_getenv(t_list **env, char *name, char *value)
{
	char	*full_name;
	char	**split_name;
	t_list	*line;

	full_name = ft_strjoin(name, "=");
	line = *env;
	while (line)
	{
		if (!ft_strncmp((char *)line->content, full_name, ft_strlen(full_name)))
		{
			free(full_name);
			split_name = ft_split(line->content, '=');
			ft_strlcpy(value, split_name[1], BUF_SIZE);
			free_dp(split_name);
			return (value);
		}
		line = line->next;
	}
	free(full_name);
	return (0);
}

int	cmd_counter(char **all_cmd)
{
	int	i;

	i = 0;
	while (all_cmd[i])
		i++;
	return (i);
}

int	check_blank_line(char *line)
{
	int	i;

	if (!ft_strncmp(line, "\"\"\0", 3) || !ft_strncmp(line, "''\0", 3))
		return (0);
	i = -1;
	while (line[++i])
	{
		if (!ft_isblank(line[i]))
			return (1);
	}
	return (0);
}
