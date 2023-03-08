/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 13:12:20 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/08 14:16:51 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_var(t_list **env, char *rep_var, char *var_name)
{
	t_list	*line;

	line = *env;
	while (ft_strncmp(line->content, var_name, ft_strlen(var_name)))
		line = line->next;
	free(line->content);
	line->content = ft_strdup(rep_var);
	*rep_var = '?';
	free(var_name);
}

t_list	**export_cmd(t_list **env, char **new_vars)
{
	int	i;

	if (!new_vars[1] || !check_syntax(env, &new_vars[1]))
		return (env);
	i = 0;
	while (new_vars[++i])
		if (new_vars[i][0] != '?')
			ft_lstadd_back(env, ft_lstnew(ft_strdup(new_vars[i])));
	return (env);
}

void	env_cmd(t_list **env)
{
	t_list	*line;

	line = *env;
	while (line)
		(printf("%s\n", (char *) line->content), line = line->next);
}

t_list	**unset_cmd(t_list **env, char **name)
{
	char	*full_name;
	t_list	*line;
	t_list	*tmp;

	if (!name[1])
		return (ft_printf("unset: not enough arguments\n"), env);
	full_name = ft_strjoin(name[1], "=");
	line = *env;
	while (line)
	{
		if (!ft_strncmp((char *)line->content, full_name, ft_strlen(full_name)))
		{
			ft_lstdelnode(env, line, tmp);
			break ;
		}
		tmp = line;
		line = line->next;
	}
	free(full_name);
	return (env);
}
