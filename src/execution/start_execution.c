/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:44:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/20 21:19:02 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	try_parent_builtins(t_cmd *cmd, t_env **env)
{
	if (cmd->args != NULL)
	{
		if (ft_strcmp("exit", cmd->args[0]) == 0)
			return (ft_exit(cmd, env));
		if (ft_strcmp("cd", cmd->args[0]) == 0)
			return (ft_cd(cmd, env));
		else if (ft_strcmp("unset", cmd->args[0]) == 0)
			return (ft_unset(cmd, env));
		else if (ft_strcmp("export", cmd->args[0]) == 0)
			return (ft_export(cmd, env));
	}
	return (0);
}

int	try_child_builtins(t_cmd *cmd, t_env **env)
{
	if (cmd->args != NULL)
	{
		if (ft_strcmp("export", cmd->args[0]) == 0)
			return (print_env_export(env));
		if (ft_strcmp("pwd", cmd->args[0]) == 0)
			return (ft_pwd());
		if (ft_strcmp("echo", cmd->args[0]) == 0)
			return (ft_echo(cmd));
		if (ft_strcmp("env", cmd->args[0]) == 0)
			return (ft_env(env));
	}
	return (0);
}

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

void prep_in_files(t_cmd *cmd)
{
	int fd;
	t_rdr *file;

	file = cmd->input;
	while (file != NULL)
	{
		if (file->type == REDL || file->type == PREPPED_HEREDOC)
			fd = (open(file->file, O_RDONLY));
		if (fd < 0)
			return ;
		if (file->args != NULL)
			update_io_args(cmd, file);
		file = file->next;
		close(fd);
	}
}

void prep_out_files(t_cmd *cmd)
{
	int fd;
	t_rdr *file;

	file = cmd->output;
	while (file != NULL)
	{
		if (file->type == REDR)
			fd = (open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0666)); //O_TRUNC delete past shit
		else if (file->type == REDRR)
			fd = (open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0666));
		if (fd < 0)
			return ;
		// if current node has args then add them to cmd->args so they get executed right
		if (file->args != NULL)
			update_io_args(cmd, file);
		file = file->next;
		close(fd);
	}
}

void	prep_redirections(t_cmd *cmd)
{
	int	hd_c;

	hd_c = cmdline_heredogs_count(cmd);
	//---------check if cmdline contains heredog
	if (hd_c > 0)
		prep_heredogs(cmd);
	while (cmd)
	{
		if (cmd->input)
			prep_in_files(cmd);
		if (cmd->output)
			prep_out_files(cmd);
		cmd = cmd->next;
	}
}

void	try_execute(t_cmd **commands, t_env **env)
{
	t_cmd	*cmd;
	int		pid;

	pid = 0;
	cmd = *commands;
	prep_redirections(cmd);
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
	if (g_global.fd_in > -1)
		close(g_global.fd_in);
	if (g_global.fd_out > -1)
		close(g_global.fd_out);
	waitpid(pid, &g_global.signal, 0);
	g_global.signal = WEXITSTATUS(g_global.signal);
}
