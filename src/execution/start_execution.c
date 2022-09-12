/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:44:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/09/12 09:43:23 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//tries to execute builtins
//if one of them executed successfully returns 0;
//else returns 1;
int	try_builtins(t_cmd **commands, t_env **env)
{
	t_cmd	*temp;

	temp = *commands;
	ft_exit(temp, env);
	if (ft_echo(temp) == 0
		|| ft_pwd(temp) == 0
		|| ft_cd(temp, env) == 0
		|| ft_env(temp, env) == 0
		|| ft_export(temp, env) == 0
		|| ft_unset(temp, env) == 0)
		return (0);
	return (1);
}

int	ft_execs(t_cmd **cmd, char **env_s, char **path)
{
	int		i;
	char	*str;
	t_cmd	*temp;

	temp = *cmd;
	i = 0;
	while (path[i] != NULL)
	{
		str = ft_strjoin(path[i], "/");
		str = ft_strjoin(str, temp->args[0]);
		if (execve(str, temp->args, env_s) != -1)
			return 0;
		i++;
	}
	printf("mininshell: %s: command not found\n", temp->args[0]);
	return (0);
}

//function that is called from main
//tryes to run builtins first
//if not succeed need to make fork 
//and call OG function from bash
void	try_execute(t_cmd **commands, t_env **env)
{
	int		pid;
	t_env	*temp;
	char	**path;

	temp = find_node_by_key(*env, "PATH");
	path = ft_split(temp->val, ':');
	// if (try_builtins(commands, env) == 0)
	// 	return ;
	pid = fork();
	if (pid == 0)
		ft_execs(commands, env_list_to_string(*env), path);
	wait(0);
}
