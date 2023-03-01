/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:49:00 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/01 16:49:48 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_str(t_list **head)
{
	t_list	*line;
	char	*full_line;
	char	*appended_line;

	line = *head;
	full_line = malloc(sizeof(char *));
	*full_line = 0;
	while (line)
	{
		appended_line = ft_strjoin(full_line, (char *)line->content);
		free(full_line);
		full_line = appended_line;
		line = line->next;
	}
	ft_lstclear(head, (*free));
	free(head);
	return (full_line);
}

void	expand_vars(char *line, t_cmdtable *rl, t_list **head, int *i)
{
	char	value[BUF_SIZE];
	char	*name;

	ft_lstadd_back(head, ft_lstnew(ft_substr(line, i[1], i[0] - i[1])));
	i[1] = i[0]++;
	if (line[i[0]] == '?')
		(ft_lstadd_back(head, ft_lstnew(ft_itoa(WEXITSTATUS(rl->status)))),
			i[0]++);
	else
	{
		while (ft_isalnum(line[i[0]]))
			i[0]++;
		name = ft_substr(line, i[1] + 1, i[0] - i[1] - 1);
		if (ft_getenv(rl->env, name, value))
			ft_lstadd_back(head, ft_lstnew(ft_strdup(value)));
		free(name);
	}
	i[1] = i[0];
}

char	*check_vars(t_cmdtable *rl, char *line)
{
	t_list	**head;
	int		i[2];

	i[0] = -1;
	i[1] = 0;
	head = malloc(sizeof(t_list **));
	*head = 0;
	while (line[++i[0]])
	{
		while (line[i[0]] == DOLLAR)
			expand_vars(line, rl, head, i);
	}
	ft_lstadd_back(head, ft_lstnew(ft_substr(line, i[1], i[0] - i[1])));
	return (free(line), append_str(head));
}

char	**expand_metachar(t_cmdtable *rl, char **rev_cmd)
{
	int	i;

	i = -1;
	while (rev_cmd[++i])
	{
		rev_cmd[i] = check_vars(rl, rev_cmd[i]);
		rev_cmd[i] = restore_vars(rev_cmd[i]);
	}
	return (rev_cmd);
}