/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:36:43 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/09 19:07:03 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_cmdtable *rl)
{
	if (!ft_strncmp(rl->cmd[0], "exit\0", 5))
		exit(free_dp(rl->cmd, 1));
	else if (!ft_strncmp(rl->cmd[0], "pwd\0", 4))
		exit(pwd_cmd());
	else if (!ft_strncmp(rl->cmd[0], "cd\0", 3))
		exit(cd_cmd(rl->cmd[1]));
	else if (!ft_strncmp(rl->cmd[0], "echo\0", 5))
		exit(echo_cmd(rl->cmd));
	else if (!ft_strncmp(rl->cmd[0], "env\0", 4))
		exit(env_cmd(environ));
	// else if (!ft_strncmp(rl->cmd[0], "export\0", 7))
	// 	environ = export_cmd(rl->cmd, rl->env_address);
	// else if (!ft_strncmp(rl->cmd[0], "#", 1))
	// 	return ;
	else
		ft_execute_cmd(rl);
}

void	red_pipe_child(t_cmdtable *rl, int i)
{
	if (i == 0 && rl->infile)// si es el 1er cmd y existe archivo de entrada
		dup2(rl->infile, 0);
	if ((i == (int)rl->n_cmd -1) && rl->outfile)// si es el ultimo y existe archivo de salida
		dup2(rl->outfile, 1);
	if (i != (int)rl->n_cmd -1)// si hay un cmd a ejecutar despues
	{
		close(rl->pipe[0]);// cierra lectura
		dup2(rl->pipe[1], 1);// cambia la salida al pipe de escritura
		close(rl->pipe[1]);// cierra escritura
	}
}

void	red_pipe_parent(t_cmdtable *rl)
{
	close(rl->pipe[1]);// cierra escritura
	dup2(rl->pipe[0], 0);// <- EL PROBLEMA
	close(rl->pipe[0]);// cierra lectura
}

void	manage_line(t_cmdtable *rl)
{
	int		pid;
	int		i;
	int		status;

	rl->all_cmd = ft_split(rl->line, '|');
	free(rl->line);
	rl->n_cmd = cmd_counter(rl);
	//check_in_out_file(rl);
	i = -1;
	while (i < (int)rl->n_cmd -1)
	{
		i++;
		if (i != (int)rl->n_cmd -1)// solo es necesario pipe si hay otro cmd que ejecutar despues
		{
			if (pipe(rl->pipe) == -1)
				perror("pipe");
		}
		pid = fork();
		if (!pid)
		{
			rl->cmd = ft_split(rl->all_cmd[i], ' ');
			free(rl->all_cmd[i]);
			red_pipe_child(rl, i);
			exec_command(rl);
			free_dp(rl->cmd, 0);
		}
		if (i != (int)rl->n_cmd -1)
			red_pipe_parent(rl);
		wait(&status);
		if (WEXITSTATUS(status) == 1)
			exit(0);
	}
}

int	main(void)
{
	t_cmdtable	rl;

	while (1)
	{
		rl.line = readline("minishell$ ");
		if (!*rl.line)
		{
			free(rl.line);
			continue ;
		}
		add_history(rl.line);
		manage_line(&rl);
	}
	return (0);
}
