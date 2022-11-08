/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:37:03 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/08 12:50:46 by mraspors         ###   ########.fr       */
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

int		count_cmd_nodes(t_cmd *cmd)
{
	int		i;
	t_cmd	*temp;

	temp = cmd;
	i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void exec_pipes(t_cmd *cmd, t_env **env)
{
	//-----update-------------------
	int		**fd; // fd[0]->read fd[1]->write
	pid_t	pid;
	int		fd_in;
	int		nodes;
	int		i;

	i = 0;
	nodes = count_cmd_nodes(cmd);
	fd = (int**)malloc(nodes * sizeof(int *));
	while (i < nodes)
	{
		fd[i] = malloc(2 * sizeof(int));
		i++;
	}
	i = 0;
	fd_in = STDIN_FILENO;
	while (cmd != NULL)
	{
		if (pipe(fd[i]) == -1)
		{
			printf("pipe fked\n");
		}
		cmd->fd_out = fd[i][1];
		pid = make_baby_pipe(fd_in, cmd, env);
		wait(0);
		if (pid == -1)
		{
			printf("fork error");
			return ;
		}
		close(fd[i][1]);
		fd_in = fd[i][0];
		cmd = cmd->next;
		i++;
	}
	i = 0;
	while (i < nodes)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 0;
	while (i < nodes)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
	wait(0);
	//-----update-------------------
}