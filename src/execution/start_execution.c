/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:44:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/05 07:13:11 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	try_parent_builtins(t_cmd *cmd, t_env **env)
{
	if (cmd->args != NULL)
	{
		if (ft_strcmp("exit", cmd->args[0]) == 0)
			ft_exit(cmd, env);
		if (ft_strcmp("cd", cmd->args[0]) == 0)
			return (ft_cd(cmd, env));
		else if (ft_strcmp("unset", cmd->args[0]) == 0)
			return (ft_unset(cmd, env));
		else if (ft_strcmp("export", cmd->args[0]) == 0)
			return (ft_export(cmd, env));
	}
	return (0);
}

void	try_child_builtins(t_cmd *cmd, t_env **env)
{
	if (cmd->args != NULL)
	{
		if (ft_strcmp("export", cmd->args[0]) == 0)
			print_env_export(cmd, env);
		if (ft_strcmp("pwd", cmd->args[0]) == 0)
			ft_pwd(cmd);
		if (ft_strcmp("echo", cmd->args[0]) == 0)
			ft_echo(cmd);
		if (ft_strcmp("env", cmd->args[0]) == 0)
			ft_env(cmd, env);
	}
}

void	ft_execs(t_cmd *cmd, t_env **env)
{
	int		i;
	char	*str;
	char	*temp;
	char	**env_s;
	char	**path;

	i = 0;
	if (check_minishell_exec(cmd, env) == 1)
	{
		free_cmd(&cmd);
		free_list(env);
		exit(0);
	}
	try_child_builtins(cmd, env);
	env_s = env_list_to_string(*env);
	path = ft_split(find_node_by_key(*env, "PATH")->val, ':');
	while (path[i] != NULL)
	{
		temp = ft_strjoin(path[i], "/");
		str = ft_strjoin(temp, cmd->args[0]);
		free(temp);
		execve(str, cmd->args, env_s);
		free(str);
		i++;
	}
	printf("mininshell: %s: command not found\n", cmd->args[0]);
	free_cmd(&cmd);
	free_list(env);
	free_doublptr(env_s);
	free_doublptr(path);
	exit(0);
}

void	try_execute(t_cmd **commands, t_env **env)
{
	t_cmd	*cmd;
	int		pid;

	cmd = *commands;
	if (cmd->next == NULL)
	{
		if (cmd->input != NULL || cmd->output != NULL)
		{
			pid = fork();
			if (pid == 0)
				exec_redir(cmd, env);
		}
		else
		{
			if (try_parent_builtins(cmd, env) == 1)
				return ;
			pid = fork();
			if (pid == 0)
				ft_execs(cmd, env);
		}
	}
	else
	{
		pid = fork();
		if (pid == 0)
			exec_pipes(cmd, env);
	}
	wait(0);
}
