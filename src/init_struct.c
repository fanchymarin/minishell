/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:32:08 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/21 20:12:28 by fmarin-p         ###   ########.fr       */
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
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}
}

t_cmdtable	init_struct(void)
{
	t_cmdtable			rl;
	struct sigaction	sig;

	rl.infile = 0;
	rl.outfile = 1;
	rl.env = clone_env();
	sig.sa_handler = &signal_handler;
	sigaction(SIGINT, &sig, 0);
	return (rl);
}
