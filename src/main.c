/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:36:43 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/04/20 19:48:56 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	// rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

int	main(void)
{
	t_cmdtable	rl;

	rl = init_struct();
	while (1)
	{
		signal(SIGINT, &signal_handler);
		rl.line = readline("minishell$ ");
		if (!rl.line)
			(ft_lstclear(rl.env, (*free)), exit(0));
		if (!*rl.line || !check_blank_line(rl.line))
		{
			free(rl.line);
			continue ;
		}
		add_history(rl.line);
		rl.line = quotes_checker(rl.line);
		if (!rl.line)
			continue ;
		rl.all_cmd = expand_metachar(&rl, ft_split(rl.line, '|'));
		rl.n_cmd = cmd_counter(rl.all_cmd);
		execute_line(&rl);
	}
	return (0);
}
