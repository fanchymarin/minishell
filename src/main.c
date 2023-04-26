/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:36:43 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/04/26 13:19:14 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waiting_parent(t_cmdtable *rl)
{
	(signal(SIGINT, SIG_IGN), check_perror(wait(&rl->status), "wait"));
	if (WTERMSIG(rl->status) == SIGINT)
		(ft_putchar_fd('\n', STDOUT_FILENO), rl->status = exit_status(130));
	else if (WTERMSIG(rl->status) == SIGQUIT)
		(ft_putchar_fd('\n', STDOUT_FILENO), rl->status = exit_status(131));
}

void	signal_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void	execute_line(t_cmdtable *rl)
{
	if (rl->n_cmd <= 0)
		error_msg(PIPE);
	check_perror(rl->stdfiles[0] = dup(STDIN_FILENO), "dup");
	check_perror(rl->stdfiles[1] = dup(STDOUT_FILENO), "dup");
	if (rl->n_cmd == 1)
		execute_single_cmd(rl);
	else
		execute_multiple_cmds(rl);
	(dup2(rl->stdfiles[STDIN_FILENO], STDIN_FILENO),
		close(rl->stdfiles[STDIN_FILENO]));
	(dup2(rl->stdfiles[STDOUT_FILENO], STDOUT_FILENO),
		close(rl->stdfiles[STDOUT_FILENO]));
	(free_dp(rl->all_cmd), free(rl->line));
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
