/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:32:08 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/23 16:18:20 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lstoarr(t_list **head)
{
	t_list	*node;
	char	**array;
	int		i;

	i = 0;
	node = *head;
	array = malloc(sizeof(char *) * (ft_lstsize(node) + 1));
	while (node)
	{
		array[i++] = ft_strdup(node->content);
		node = node->next;
	}
	array[i] = 0;
	return (array);
}

t_list	**clone_env(void)
{
	extern char	**environ;
	t_list		**new_env;
	int			i;

	i = -1;
	new_env = malloc(sizeof(t_list **));
	*new_env = 0;
	while (environ[++i])
		ft_lstadd_back(new_env, ft_lstnew(ft_strdup(environ[i])));
	return (new_env);
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

t_cmdtable	init_struct(void)
{
	t_cmdtable			rl;
	struct sigaction	sigint;

	rl_catch_signals = 0;
	rl.here_doc = 0;
	rl.infile = 0;
	rl.outfile = 0;
	rl.status = 0;
	rl.env = clone_env();
	sigint.sa_handler = &signal_handler;
	sigaction(SIGINT, &sigint, 0);
	signal(SIGQUIT, SIG_IGN);
	return (rl);
}
