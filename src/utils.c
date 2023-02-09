/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:55:15 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/09 19:07:04 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_dp(char **dp, int status)
{
	int	i;

	i = 0;
	while (dp[i])
		free(dp[i++]);
	free(dp);
	return (status);
}