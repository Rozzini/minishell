/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:44:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/28 22:18:57 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	try_builtins(t_cmd *cmd, t_env **env)
{
	char	*s;

	s = NULL;
	if (cmd->args != NULL)
		s = cmd->args[0];
	else
		return ;
	if (ft_strcmp("cd", s) == 0)
		ft_cd(cmd, env);
	if (ft_strcmp("pwd", s) == 0)
		ft_pwd(cmd);
	if (ft_strcmp("echo", s) == 0)
		ft_echo(cmd);
	if (ft_strcmp("unset", s) == 0)
		ft_unset(cmd, env);
	if (ft_strcmp("env", s) == 0)
		ft_env(cmd,env);
	if (ft_strcmp("export", s) == 0)
		ft_export(cmd, env);
}

int	ft_execs(t_cmd *cmd, t_env **env)
{
	int		i;
	char	*str;
	char	*temp;
	char	**env_s;
	char	**path;

	i = 0;
	try_builtins(cmd, env);
	if (cmd->args == NULL)
	{
		printf("empty command\n");
		return(0);
	}
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
	int		pid;
	t_cmd	*cmd;

	cmd = *commands;
	ft_exit(cmd, env);
	if  (check_heredoc(cmd))
	{
		exec_heredog(1, cmd);
		return ;
	}
	if (cmd->next == NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmd->input != NULL || cmd->output != NULL)
				exec_redir(cmd, env);
			else
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
