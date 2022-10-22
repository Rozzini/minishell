/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:22:37 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/22 16:55:33 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//gotta read from file
int open_files_input(t_cmd *cmd)
{
	int fd;
	t_rdr *file;

	file = cmd->output;
	while (file->next != NULL)
	{
		if (file->type == REDL)
			fd = (open(cmd->output->file, O_RDONLY));
		// else if (file->type == HEREDOC)
		// 	fd = (open(file->file));
		file = file->next;
		close(fd);
	}
	if (file->type == REDL)
		return (open(cmd->output->file, O_RDONLY));
	// else if (file->type == HEREDOC)
	// 	return (open(file->file));
	return (0);
	if (cmd->input->type == REDL)
		return (open(cmd->output->file, O_RDONLY));
	return (STDIN_FILENO);
}

int open_file_out(t_cmd *cmd)
{
	if (cmd->output->type == REDR)
		return (open(cmd->output->file, O_WRONLY | O_CREAT | O_TRUNC, 0666));
	if (cmd->output->type == REDRR)
		return (open(cmd->output->file, O_WRONLY | O_APPEND | O_CREAT, 0666));
	return (STDOUT_FILENO);
}
/*
t_file
{
	char *file
	int type
	t_file *next
}
*/

int open_files_output(t_cmd *cmd)
{
	int fd;
	t_rdr *file;

	file = cmd->output;
	while (file->next != NULL)
	{
		if (file->type == REDR)
			fd = (open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0666));
		else if (file->type == REDRR)
			fd = (open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0666));
		file = file->next;
		close(fd);
	}
	if (file->type == REDR)
		return (open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0666));
	else if (file->type == REDRR)
		return (open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0666));
	return (0);
}

int redirect(t_cmd *cmd, t_env **env, char **path)
{
	pid_t pid;
	int fd_in;
	int fd_out;
	int pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (1);
	// if (fd < 0)
	// 	return (1);
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	pid = fork();
	if (pid < 0)
	{
		printf("fork failed\n");
		exit(0);
	}
	else if (pid == 0)
	{
		// fd_in = open_file_r(cmd);
		if (cmd->output->file)
		{
			fd_out = open_files_output(cmd);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
			return (ft_execs(cmd, env, path));
		}
		if (cmd->input->file)
		{
			fd_in = open_file_in(cmd);//WIP
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
			return(ft_execs(cmd, env, path));
		}
	}
	else
	{
		close(fd_out);
		close(fd_in);
		wait(0);
	}
	return (0);
}

int exec_redir(t_cmd *cmd, t_env **env, char **path)
{
	// int		fd_in;
	// int		fd_out;
	// pid_t	pid;

	// while (curr_cmd != NULL)
	// {
	printf("currcmd: %s\n", cmd->args[0]);
	if (redirect(cmd, env, path) == -1)
	{
		printf("redir fork/dup error\n");
		return (1);
	}
	// 	curr_cmd = curr_cmd->next;
	// }
	return (0);
}