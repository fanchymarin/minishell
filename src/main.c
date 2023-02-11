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
	close(rl->pipe[0]);// cierra canal de lectura 
	if (i == 0 && rl->infile)// si existe archivo de entrada y es el primer cmd
		dup2(rl->infile, 0);
	if ((i + 1 == (int)rl->n_cmd) && rl->outfile)// si existe archivo de salida y es el ultimo cmd
		dup2(rl->outfile, 1);
	if (i + 1 != (int)rl->n_cmd)// si hay mas de 1 cmd y no es el 'ultimo cmd
		dup2(rl->pipe[1], 1);
	close(rl->pipe[1]);// cierra canal de lectura 
}

void	red_pipe_parent(t_cmdtable *rl)
{
	close(rl->pipe[1]);// el padre cierra la escritura
	dup2(rl->pipe[0], 0);// cambia la lectura para que sea la salida del hijo
	close(rl->pipe[0]);// cierra la lectura
}

void	manage_line(t_cmdtable *rl)
{
	int		pid;
	int		i;
	int		status;

	rl->all_cmd = ft_split(rl->line, '|');
	free(rl->line);
	rl->n_cmd = cmd_counter(rl);
	i = -1;
	while (i < (int)rl->n_cmd)
	{
		i++;
		if (pipe(rl->pipe) == -1)
			perror("pipe");
		pid = fork();
		if (!pid)
		{
			rl->cmd = ft_split(rl->all_cmd[i], ' ');
			// free(rl->all_cmd[i]);
			red_pipe_child(rl, i);
			exec_command(rl);// despues de execve el proceso muere x eso no se liberaria el cmd
			break;
		}
		else
		{
			red_pipe_parent(rl);
			wait(&status);
			if (WEXITSTATUS(status) == 1)
				exit(0);
			//free_dp(rl->cmd, 0); si libera no ejecuta cmds, asi que me imagino que esta sobrescribiendo
		}
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
