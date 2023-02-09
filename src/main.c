/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:36:43 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/05 14:14:56 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_prompt *tty)
{
	if (!ft_strncmp(tty->word[0], "exit\0", 5))
		free_struct(tty, 1);
	else if (!ft_strncmp(tty->word[0], "pwd\0", 4))
		pwd_cmd();
	else if (!ft_strncmp(tty->word[0], "cd\0", 3))
		cd_cmd(tty->word[1]);
	else if (!ft_strncmp(tty->word[0], "echo\0", 5))
		echo_cmd(tty->word);
	else if (!ft_strncmp(tty->word[0], "env\0", 4))
		env_cmd(environ);
	else if (!ft_strncmp(tty->word[0], "export\0", 7))
		environ = export_cmd(tty->word, tty->env_address);
	else if (!ft_strncmp(tty->word[0], "#", 1))
		return;
	// else
	// 	parent_process(tty);
}

int	main(void)
{
	t_prompt	tty;

	tty.env_address = &environ;
	while (1)
	{
		tty.rl_line = readline("minishell$ ");
		tty.line = ft_strtrim(tty.rl_line, " ");
		if (!*tty.line)
		{
			free(tty.rl_line);
			free(tty.line);
			continue ;
		}
		add_history(tty.line);
		tty.word = ft_split(tty.line, ' ');
		exec_command(&tty);
		free_struct(&tty, 0);
	}
	return (0);
}
