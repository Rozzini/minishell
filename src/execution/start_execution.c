/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:44:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/18 15:12:50 by mraspors         ###   ########.fr       */
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
	char	*command_error;

	if (check_minishell_exec(cmd, env) == 1
		|| try_child_builtins(cmd, env) == 1)
	{
		free_cmd(&cmd);
		free_list(env);
		exit(0);
	}
	ft_execve(cmd, env);
	command_error = ft_strdup(cmd->args[0]);
	write(2, "minishell: ", 11);
	write(2, command_error, ft_strlen(command_error));
	write(2, ": command not found\n", 20);
	free(command_error);
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
		{
			printf("%s: No such file or directory\n", file->file); //make it >
			return ;
		}
		if (file->args != NULL)
			update_in_args(cmd, file);
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
			update_out_args(cmd, file);
		file = file->next;
		close(fd);
	}
}

void	prep_redirections(t_cmd *cmd)
{
	int	hd_c;

	hd_c = cmdline_heredogs_count(cmd);
	printf("prep redir\n");
	//---------check if cmdline contains heredog
	if (hd_c > 0)
	{
			printf("prep heredogs with %d\n", hd_c);
			prep_heredogs(cmd);
	}
	while (cmd)
	{
		if (cmd->input)
		{
			printf("open input files\n");
			prep_in_files(cmd);
		}
		if (cmd->output)
		{
			printf("open output files\n");
			prep_out_files(cmd);
		}
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
		printf("x\n");
		pid = fork();
		if (pid == 0)
			exec_pipes(cmd, env);
	}
	waitpid(pid, &g_global.signal, 0);
	g_global.signal = WEXITSTATUS(g_global.signal);
}
