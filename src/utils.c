/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:55:15 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/03 18:08:36 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dp(char **dp)
{
	int	i;

	i = 0;
	while (dp[i])
		free(dp[i++]);
	free(dp);
}

void	free_struct(t_prompt *tty, int stat)
{
	free(tty->rl_line);
	free(tty->line);
	free_dp(tty->word);
	if (stat)
	{
		free(tty);
		exit(0);
	}
}

t_dbarray	find_size_dbarray(char **environ)
{
	t_dbarray	size;
	int			i;
	int			j;

	size.lines = 0;
	while (environ[size.lines])
		size.lines++;
	size.chars = malloc(sizeof(int) * size.lines);
	i = 0;
	while (i < size.lines)
	{
		j = 0;
		while (environ[i][j])
			++j;
		size.chars[i++] = j;
	}
	return (size);
}