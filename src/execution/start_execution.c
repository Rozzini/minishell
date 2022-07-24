/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:44:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/24 22:06:49 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//tries to execute builtins
//if one of them executed successfully returns 0;
//else returns 1;
int	try_builtins(t_tokens *tokens, t_env **env)
{
	ft_exit(tokens, env);
	if (ft_echo(tokens) == 0
		|| ft_pwd(tokens) == 0
		|| ft_cd(tokens, env) == 0
		|| ft_env(tokens, env) == 0
		|| ft_export(tokens, env) == 0
		|| ft_unset(tokens, env) == 0)
		return (0);
	return (1);
}

int	ft_execs(t_tokens *tokens, char **env)
{
	char	cmd[] = "/usr/bin/";
	char	*str = ft_strjoin(cmd, tokens->args[0]);
	char	*arg_vec[] = {tokens->args[0], tokens->args[1], NULL};

	if (execve(str, arg_vec, env) == -1)
	{
		free (str);
		str = ft_strjoin("/bin/", tokens->args[0]);
		if (execve(str, arg_vec, env) == -1)
			printf("mininshell: %s: command not found\n", tokens->args[0]);
	}
	return (0);
}

//function that is called from main
//tryes to run builtins first
//if not succeed need to make fork 
//and call OG function from bash
void	try_execute(t_tokens *tokens, t_env **env)
{
	int		pid;
	char	**env_s;

	if (try_builtins(tokens, env) == 0)
		return ;
	env_s = env_list_to_string(*env);
	pid = fork();
	if (pid == 0)
		ft_execs(tokens, env_s);
	wait(0);
}
