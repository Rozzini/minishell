/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:44:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/22 16:37:30 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//tries to execute builtins
//if one of them executed successfully returns 0;
//else returns 1;
int	try_builtins(t_cmd *cmd, t_env **env)
{
	ft_exit(cmd, env);
	if (ft_echo(cmd) == 0
		|| ft_pwd(cmd) == 0
		|| ft_cd(cmd, env) == 0
		|| ft_env(cmd, env) == 0
		|| ft_export(cmd, env) == 0
		|| ft_unset(cmd, env) == 0)
		return (0);
	return (1);
}

int	ft_execs(t_cmd *cmd, t_env **env, char **path)
{
	int		i;
	char	*str;
	char	**env_s;

	i = 0;
	env_s = env_list_to_string(*env);
	if (try_builtins(cmd, env) == 0)
		return (0);
	if (cmd->args == NULL)
	{
		printf("empty command\n");
		return(0);
	}
	while (path[i] != NULL)
	{
		str = ft_strjoin(path[i], "/");
		str = ft_strjoin(str, cmd->args[0]);
		if (execve(str, cmd->args, env_s) != -1)
			return (0);
		i++;
	}
	printf("mininshell: %s: command not found\n", cmd->args[0]);
	return (0);
}

//function that is called from main
//tryes to run builtins first
//if not succeed need to make fork 0--
//and call OG function from bash
void	try_execute(t_cmd **commands, t_env **env, char **path)
{
	int		pid;
	t_cmd	*cmd;

	cmd = *commands;
	if (cmd->next == NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmd->input != NULL || cmd->output != NULL)
				exec_redir(cmd, env, path);
			else
				ft_execs(cmd, env, path);
		}
	}
	else
	{
		pid = fork();
		if (pid == 0)
			exec_pipes(cmd, env, path);
	}
	wait(0);
}
