/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:44:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/20 23:25:03 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_execve(t_cmd *cmd, t_env **env)
{
	int		i;
	char	*str;
	char	*temp;
	char	**env_s;
	char	**path;

	i = 0;
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
	free_doublptr(env_s);
	free_doublptr(path);
}

void	ft_execs(t_cmd *cmd, t_env **env)
{
	if (check_minishell_exec(cmd, env) == 1
		|| try_child_builtins(cmd, env) == 1)
	{
		free_cmd(&cmd);
		free_list(env);
		exit(0);
	}
	ft_execve(cmd, env);
	er_ft_execs(cmd->args[0]);
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	free_cmd(&cmd);
	free_list(env);
	exit(127);
}

void	try_execute_helper(t_cmd *cmd, t_env **env, int *pid)
{
	if (cmd->next == NULL)
	{
		if (cmd->input != NULL || cmd->output != NULL)
		{
			*pid = fork();
			if (*pid == 0)
				exec_redir(cmd, env);
		}
		else
		{
			if (try_parent_builtins(cmd, env) == 1)
				return ;
			*pid = fork();
			if (*pid == 0)
				ft_execs(cmd, env);
		}
	}
	else
	{
		*pid = fork();
		if (*pid == 0)
			exec_pipes(cmd, env);
	}
}

void	try_execute(t_cmd **commands, t_env **env)
{
	t_cmd	*cmd;
	int		pid;

	pid = 0;
	cmd = *commands;
	prep_redirections(cmd);
	try_execute_helper(cmd, env, &pid);
	if (g_global.fd_in > -1)
		close(g_global.fd_in);
	if (g_global.fd_out > -1)
		close(g_global.fd_out);
	waitpid(pid, &g_global.signal, 0);
	g_global.signal = WEXITSTATUS(g_global.signal);
}
