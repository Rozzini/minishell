/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 04:22:10 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/03 23:42:18 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	sig_exit_code(int flag)
// {
// 	static int	exit = -1;

// 	if (flag == SIGINT)
// 		exit = 130;
// 	else if (flag == -69)
// 		exit = -1;
// 	return (exit);
// }

void	sig_handler(int sig)
{
    if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}