/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:34:40 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/05 14:02:56 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h> 

typedef struct s_prompt
{
	char	*rl_line;
	char	*line;
	char	**word;
	char	***env_address;
	char	**oper;
	char	***cmd_lines; //liberarlo en free_struct?
	int		n_cmd;
	int		n_oper;
}	t_prompt;

typedef struct s_dbarray
{
	int	lines;
	int	new_lines;
}	t_dbarray;

extern char	**environ;

void		free_dp(char **dp);
void		free_struct(t_prompt *tty, int stat);
int			check_syntax_n_size(char **new_vars);

void		pwd_cmd(void);
void		cd_cmd(char *dir);
void		echo_cmd(char **word);
void		env_cmd(char **environ);
char		**export_cmd(char **new_vars, char ***env_address);

char		*ft_find_path(char *cmd);
void		child_process(t_prompt *tty, int i);
int			parent_process(t_prompt *tty);

void		cmd_counter(t_prompt *tty);
void		split_line(t_prompt *tty);

#endif
