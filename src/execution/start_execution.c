/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:44:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/16 18:43:06 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

// tries to execute builtins
// if one of them executed successfully returns 0;
// else returns 1;
int try_builtins(t_cmd *cmd, t_env **env)
{
	ft_exit(cmd, env);
	if (ft_echo(cmd) == 0 || ft_pwd(cmd) == 0 || ft_cd(cmd, env) == 0 || ft_env(cmd, env) == 0 || ft_export(cmd, env) == 0 || ft_unset(cmd, env) == 0)
		return (0);
	return (1);
}

int ft_execs(t_cmd *cmd, t_env **env, char **path)
{
	int i;
	char *str;
	char **env_s;

	i = 0;
	env_s = env_list_to_string(*env);
	if (try_builtins(cmd, env) == 0)
		return (0);
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

int make_baby(int fd_in, int fd_out, t_cmd *cmd, char **path, t_env **env)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (fd_in != 0)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (fd_out != 1)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		return ft_execs(cmd, env, path);
	}
	return (pid);
}

void exec_pipes(t_cmd *cmd, t_env **env, char **path, int n_cmd)
{
	int fd[2]; // fd[0]->read fd[1]->write
	int prev_fd;
	int i;
	pid_t pid;
	t_cmd *curr_cmd;

	//first process  getS input from the stdin->0
	prev_fd = 0;
	i = 1;
	curr_cmd = cmd;
	//make all child processes except for last which we will redirect to stdout
	printf("	no of cmds:%d\n", n_cmd);
	//while (i < n_cmd)
	while (curr_cmd->next != NULL)
	{
		pipe(fd);
		printf("	cmd i (%d): %s\n", i, curr_cmd->args[0]);
		// f[1]->write end of the pipe
		// carry `prev` from the prev iteration.
		pid = make_baby(prev_fd, fd[1], curr_cmd, path, env);
		if (pid == -1)
		{
			printf("fork error");
			return ;
		}
		//no need for write end bcz child process will use it
		close(fd[1]);
		//save fd[0] to give it to next child
		prev_fd = fd[0];
		curr_cmd = curr_cmd->next;
		i++;
	}
	printf("	last to execute and redirect to stdout:\n	cmd i (%d): %s\n", i, curr_cmd->args[0]);
	//last cmd on pipe: set stdin be the read end of the prev pipe
	//and output to the original STDOUT
	if (prev_fd != 0)
		dup2(prev_fd, 0);
	ft_execs(curr_cmd, env, path);
	return;
}

// //maks's

int n_cmds(t_cmd *head)
{
	int count = 0;
	t_cmd *current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

// function that is called from main
// tryes to run builtins first
// if not succeed need to make fork 0--
// and call OG function from bash
void try_execute(t_cmd **commands, t_env **env, char **path)
{
	int pid;
	t_cmd *cmd;
	int n_cmd;

	cmd = *commands;
	n_cmd = n_cmds(cmd);
	if (cmd->next == NULL)
	{
		pid = fork();
		if (pid == 0)
			ft_execs(cmd, env, path);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			exec_pipes(cmd, env, path, n_cmd);
	}
	wait(0);
}
