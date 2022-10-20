/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:22:37 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/20 11:55:39 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int exec_redr(int fd, t_cmd *cmd, t_env **env, char **path)
{
	fd = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	// instead of opening once
	// will have linked list of files to pass into a function to open and close
	// each file accordingly ---> open_files(linked_list_output, ...);
	//  ls a > b > c > ...
	if (!dup2(fd, STDOUT_FILENO))
		return (1);
	close(fd);
	return (ft_execs(cmd, env, path));
}

int exec_redrr(int fd, t_cmd *cmd, t_env **env, char **path)
{
	fd = open(cmd->output, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (!dup2(fd, STDOUT_FILENO))
		return (1);
	close(fd);
	if (ft_execs(cmd, env, path))
		return (1);
	return (0);
}

int exec_inputs(t_cmd *cmd, t_env **env, char **path)
{
	int fd_in;

	if (cmd->in_type == REDL)
	{
		fd_in = open(cmd->input, O_RDONLY);
		if (!dup2(fd_in, STDIN_FILENO))
			return (1);
		close(fd_in);
		ft_execs(cmd, env, path);
	}
	if (cmd->in_type == HEREDOC)
	{
		// exec_heredoc(cmd, env, path);
	}
	return (0);
}

int make_baby_redir(t_cmd *cmd, t_env **env, char **path)
{
	pid_t	pid;
	int		fd;

	printf("cmd in_type: %d		out_type: %d\n", cmd->in_type, cmd->out_type);
	fd = 0;
	pid = fork();
	if (pid < 0)
	{
		printf("fork failed\n");
		exit(0);
	}
	else if (pid == 0)
	{
		printf("in child redir\n");
		if (cmd->out_type == REDR)
			exec_redr(fd, cmd, env, path);
		// if (cmd->out_type == REDRR)
		// 	return (exec_redrr(cmd, env, path));
		// if (cmd->out_type == REDL || cmd->out_type == HEREDOC)
		// 	exec_inputs(cmd, env, path);
	}
    else {
		close(fd);
        wait(0);
    }
	return (0);
}

void exec_redir(t_cmd *cmd, t_env **env, char **path)
{
	// int		fd[2];
	// int		fd_in;
	// int		fd_out;
	// pid_t	pid;
	t_cmd *curr_cmd;

	curr_cmd = cmd;
	// while (curr_cmd != NULL)
	// {
	printf("currcmd: %s\n", curr_cmd->args[0]);
	if (make_baby_redir(curr_cmd, env, path) == -1)
	{
		printf("redir fork/dup error\n");
		return;
	}
	// 	curr_cmd = curr_cmd->next;
	// }
}