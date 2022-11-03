/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 04:22:10 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/03 04:49:11 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	sig_exit_code(int flag)
{
	static int	exit = -1;

	if (flag == SIGINT)
		exit = 130;
	else if (flag == -69)
		exit = -1;
	return (exit);
}

void	new_line_sig(int sig)
{
    if (sig == SIGINT)
	{
		sig_exit_code(sig);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
	}
}