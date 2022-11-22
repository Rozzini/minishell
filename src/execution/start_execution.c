/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:44:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/22 22:39:41 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_execve_helper(t_cmd *cmd, t_env *p, char **env_s)
{
	int		i;
	char	*str;
	char	*temp;
	char	**path;

	i = 0;
	path = ft_split(p->val, ':');
	while (path[i] != NULL && path != NULL)
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

void	ft_execve(t_cmd *cmd, t_env **env)
{
	char	**env_s;
	t_env	*p;

	env_s = env_list_to_string(*env);
	if (ft_strchr(cmd->args[0], '/') != NULL)
		execve(cmd->args[0], cmd->args, env_s);
	p = find_node_by_key(*env, "PATH");
	if (p == NULL)
	{
		free_doublptr(env_s);
		return ;
	}
	ft_execve_helper(cmd, p, env_s);
}

void	ft_execs(t_cmd *cmd, t_env **env)
{
	if (cmd->args == NULL)
	{
		free_cmd(&cmd);
		free_list(env);
		exit(0);
	}
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
	prep_redirections(cmd, env);
	try_execute_helper(cmd, env, &pid);
	waitpid(pid, &g_global.signal, 0);
	g_global.signal = WEXITSTATUS(g_global.signal);
}
