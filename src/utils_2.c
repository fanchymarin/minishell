/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:19:20 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/01 15:06:53 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*nested_shell(char *line, char *keyword) //UTILIZAR SHELL CON .TMP
{
	char	*appended_line;
	char	*new_line;
	char	*old_line;

	appended_line = readline("> ");
	while (!ft_strchr(appended_line, *keyword))
	{
		new_line = readline("> ");
		old_line = appended_line;
		appended_line = ft_strjoin(appended_line, new_line);
		(free(old_line), free(new_line));
	}
	new_line = ft_strjoin(line, appended_line);
	(free(line), free(appended_line));
	return (new_line);
}

void	ft_lstdelnode(t_list **head, t_list *node, t_list *tmp)
{
	if (node == *head)
		*head = node->next;
	else
		tmp->next = node->next;
	free(node->content);
	free(node);
	if (!*head)
		free(head);
}

int	quotes_closed(char *line, int i, char quote)
{
	int	quotes_counter;
	int	last_quote;

	quotes_counter = 0;
	last_quote = 0;
	while (line[i])
	{
		if (line[i] == quote)
		{
			last_quote = i;
			quotes_counter++;
		}
		i++;
	}
	if (quotes_counter % 2 == 0)
		return (last_quote);
	return (-1);
}

void	close_fd(t_cmdtable *rl)
{
	pid_t	pid;
	char	**cmd;

	rl->infile = 0;
	rl->outfile = 0;
	if (rl->fd_tmp)
	{
		(close(rl->fd_tmp), rl->fd_tmp = 0);
		cmd = ft_split("rm -f .tmp", ' ');
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (!pid)
		{
			execve_cmd(rl->env, ft_find_path(cmd[0], rl->env), cmd);
			exit(0);
		}
		free_dp(cmd);
	}
}
