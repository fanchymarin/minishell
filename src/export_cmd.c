/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 13:12:20 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/05 14:42:20 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_var(char *rep_var, char *var_name)
{
	int	i;

	i = 0;
	while (ft_strncmp(environ[i], var_name, ft_strlen(var_name)))
		++i;
	environ[i] = rep_var;
	*rep_var = '?';
}

int	check_syntax_n_size(char **new_vars)
{
	int			i;
	int			new_lines;
	char		**split_var;

	i = 1;
	new_lines = 0;
	while (new_vars[i])
	{
		if (!ft_isalpha(new_vars[i][0]) || !ft_strchr(new_vars[i], '=')
			|| ft_strchr(new_vars[i], '=') != ft_strrchr(new_vars[i], '='))
		{
			printf("minishell: export: '%s': is not a valid identifier\n",
				new_vars[i]);
			*new_vars[i++] = '?';
			continue ;
		}
		split_var = ft_split(new_vars[i], '=');
		if (getenv(split_var[0]))
			replace_var(new_vars[i], split_var[0]);
		else
			new_lines++;
		i++;
		free(split_var);
	}
	return (new_lines);
}

char	**export_cmd(char **new_vars, char ***env_address)
{
	int		new_lines;
	int		i;
	int		j;
	char	**new_environ;

	new_lines = check_syntax_n_size(new_vars);
	if (!new_lines)
		return (environ);
	i = -1;
	while (environ[++i])
		new_lines++;
	new_environ = malloc(sizeof(char *) * (new_lines + 1));
	i = -1;
	while (environ[++i])
		new_environ[i] = environ[i];
	j = -1;
	while (new_vars[++j])
		if (*new_vars[j] != '?')
			new_environ[i++] = new_vars[j];
	if (env_address != &environ)
		free_dp(environ);
	return (new_environ);
}
