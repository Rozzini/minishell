/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:37:03 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/08 11:29:55 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	ft_peepeeing(int *prev_new_fd, t_cmd *cmd)
// {
// 	if (cmd->next != NULL)
// 	{
// 		if (prev_new_fd[0] != 0)
// 			dup2(prev_new_fd[0], STDIN_FILENO);
// 		if (prev_new_fd[1] != 1)
// 			dup2(prev_new_fd[1], STDOUT_FILENO);
// 	}
// 	else
// 		dup2(prev_new_fd[0], STDIN_FILENO);
// 	close(prev_new_fd[0]);
// 	close(prev_new_fd[1]);
// }

// int make_baby_pipe(int *prev_new_fd, t_cmd *cmd, t_env **env)
// {
// 	pid_t pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		ft_peepeeing(prev_new_fd, cmd);
// 		if (try_parent_builtins(cmd, env) == 1)
// 			exit (g_signal);
// 		if (cmd->input || cmd->output)
// 			exec_redir(cmd, env);
// 		else
// 			ft_execs(cmd, env);
// 		exit(g_signal);
// 	}
// 	return (pid);
// }

// void exec_pipes(t_cmd *cmd, t_env **env)
// {
// 	int fd[2];
// 	pid_t	pid;
// 	int prev_new_fd[2];

// 	prev_new_fd[0] = STDIN_FILENO;
// 	while (cmd != NULL)
// 	{
// 		if (pipe(fd) == -1)
// 		{
// 			printf("pipe fked\n");
// 		}
// 		prev_new_fd[1] = fd[1];
// 		pid = make_baby_pipe(prev_new_fd, cmd, env);
// 		wait(0);
// 		if (pid == -1)
// 		{
// 			printf("fork error");
// 			return ;
// 		}
// 		close(fd[1]);
// 		prev_new_fd[0] = fd[0];
// 		cmd = cmd->next;
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	wait(0);
// }



void	ft_peepeeing(int fd_in, t_cmd *cmd)
{
	//-----update-------------------
	if (cmd->next != NULL)
	{
		if (fd_in != 0)
			dup2(fd_in, STDIN_FILENO);
		if (cmd->fd_out != 1)
			dup2(cmd->fd_out, STDOUT_FILENO);
	}
	else
		dup2(fd_in, STDIN_FILENO);
	close(cmd->fd_out);
	close(fd_in);
	//-----update
}

int make_baby_pipe(int fd_in, t_cmd *cmd, t_env **env)
{
	//-----update-------------------
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (try_parent_builtins(cmd, env) == 1)
			exit (g_signal);
		ft_peepeeing(fd_in, cmd);
		if (cmd->input || cmd->output)
			exec_redir(cmd, env);
		else
			ft_execs(cmd, env);
		exit(g_signal);
	}
	return (pid);
	//-----update-------------------
}

void exec_pipes(t_cmd *cmd, t_env **env)
{
	//-----update-------------------
	int		fd[2]; // fd[0]->read fd[1]->write
	pid_t	pid;
	int		fd_in;

	// first process  getS input from the stdin->0
	fd_in = STDIN_FILENO;
	while (cmd != NULL)
	{
		if (pipe(fd) == -1)
		{
			printf("pipe fked\n");
		}
		// f[1]->write end of the pipe
		//when we exec->output of command goes to write end of pipe
		cmd->fd_out = fd[1]; // ***
		pid = make_baby_pipe(fd_in, cmd, env);
		wait(0);
		if (pid == -1)
		{
			printf("fork error");
			return ;
		}
		//no need for write end bcz child process will use it
		close(fd[1]);
		//save fd[0] to give it to next child
		fd_in = fd[0];
		cmd = cmd->next;
	}
	close(fd[1]);
	close(fd[0]);
	wait(0);
	//-----update-------------------
}