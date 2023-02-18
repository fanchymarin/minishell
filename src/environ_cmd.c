/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 13:12:20 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/18 02:12:57 by fmarin-p         ###   ########.fr       */
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

int	check_syntax_n_size(t_list **env, char **new_vars)
{
	int			i;
	int			new_lines;
	char		**split_var;
	char		value_buf[BUF_SIZE];

	i = -1;
	new_lines = 0;
	while (new_vars[++i])
	{
		if (!ft_isalpha(new_vars[i][0]) || !ft_strchr(new_vars[i], '=')
			|| ft_strchr(new_vars[i], '=') != ft_strrchr(new_vars[i], '='))
		{
			printf("minishell: export: '%s': is not a valid identifier\n",
				new_vars[i]);
			*new_vars[i] = '?';
			continue ;
		}
		split_var = ft_split(new_vars[i], '=');
		if (ft_getenv(env, split_var[0], value_buf))
			(replace_var(env, new_vars[i], ft_strjoin(split_var[0], "=")));
		else
			new_lines++;
		free_dp(split_var);
	}
	return (new_lines);
}

t_list	**export_cmd(t_list **env, char **new_vars)
{
	int	i;

	if (!check_syntax_n_size(env, &new_vars[1]))
		return (free_dp(new_vars), env);
	i = 0;
	while (new_vars[++i])
		if (new_vars[i][0] != '?')
			ft_lstadd_back(env, ft_lstnew(ft_strdup(new_vars[i])));
	return (free_dp(new_vars), env);
}

void	env_cmd(t_list **env)
{
	t_list	*line;

	line = *env;
	while (line)
		(printf("%s\n", (char *) line->content), line = line->next);
}

void	ft_lstdelnode(t_list *line, t_list **tmp)
{
	t_list	*prev_line;

	prev_line = *tmp;
	prev_line->next = line->next;
	free(line->content);
	free(line->next);
	free(line);
}

t_list	**unset_cmd(t_list **env, char *name)
{
	char	*full_name;
	t_list	*line;
	t_list	*tmp;

	full_name = ft_strjoin(name, "=");
	line = *env;
	while (line)
	{
		if (!ft_strncmp((char *)line->content, full_name, ft_strlen(full_name)))
			ft_lstdelnode(line, &tmp); //UNSET
		tmp = line;
		line = line->next;
	}
	free(full_name);
	return (env);
}