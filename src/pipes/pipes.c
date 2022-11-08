/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:37:03 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/08 10:03:46 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	ft_peepeeing(int fd_in, t_cmd *cmd)
{
	//-----update-------------------
	if (cmd->next != NULL)
	{
		if (fd_in != 0)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (cmd->output->fd != 1)
		{
			dup2(cmd->output->fd, STDOUT_FILENO);
			close(cmd->output->fd);
		}
	}
	else
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
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
		ft_peepeeing(cmd);
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
		cmd->output->fd = fd[1]; // ***
		pid = make_baby_pipe(fd_in, cmd, env);
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
	//-----update-------------------
}
