/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizk <mrizk@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:44:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/24 18:31:22 by mrizk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//tries to execute builtins
//if one of them executed successfully returns 0;
//else returns 1;
int	try_builtins(t_tokens *tokens, t_env **env)
{
	if (ft_echo(tokens) == 0
		|| ft_pwd(tokens) == 0
		|| ft_cd(tokens) == 0
		|| ft_env(tokens, env) == 0)
		return (0);
	return (1);
}

//function that is called from main
//tryes to run builtins first
//if not succeed need to make fork 
//and call OG function from bash
void	try_execute(t_tokens *tokens, t_env **env)
{
	if (try_builtins(tokens, env) == 0)
		return ;
	// int id = fork();
	// if(id == 0)
	// 	ft_execs(tokens, env);
	else
		wait(0);
}
