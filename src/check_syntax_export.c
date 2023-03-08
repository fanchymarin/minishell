/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:47:54 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/08 14:16:26 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name_syntax(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
	}
	return (0);
}

char	**restore_equals(char **var)
{
	int		i;
	char	*old_value;

	i = 1;
	while (var[++i])
	{
		old_value = var[1];
		var[1] = ft_strjoin(var[1], var[i]);
		free(old_value);
	}
	return (var);
}

int	more_checks(char **new_vars, int i, char **split_var)
{
	if (ft_strchr(new_vars[i], '=') != ft_strrchr(new_vars[i], '='))
		split_var = restore_equals(split_var);
	if (!split_var[0] || !split_var[1] || check_name_syntax(split_var[0]))
	{
		ft_printf("minishell: export: '%s': is not a valid identifier\n",
			new_vars[i]);
		(free_dp(split_var), *new_vars[i] = '?');
		return (1);
	}
	return (0);
}

int	check_syntax(t_list **env, char **new_vars)
{
	int			i;
	int			new_lines;
	char		**split_var;
	char		value_buf[BUF_SIZE];

	i = -1;
	new_lines = 0;
	while (new_vars[++i])
	{
		if (!ft_strchr(new_vars[i], '='))
		{
			*new_vars[i] = '?';
			continue ;
		}
		split_var = ft_split(new_vars[i], '=');
		if (more_checks(new_vars, i, split_var))
			continue ;
		if (ft_getenv(env, split_var[0], value_buf))
			(replace_var(env, new_vars[i], ft_strjoin(split_var[0], "=")));
		else
			new_lines++;
		free_dp(split_var);
	}
	return (new_lines);
}
