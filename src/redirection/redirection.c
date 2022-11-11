/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:22:37 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/11 19:21:06 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//gotta read from file
int	open_files_input(t_cmd *cmd)
{
	int		fd;
	t_rdr	*file;

	file = cmd->input;
	while (file->next != NULL)
	{
		if (file->type == REDL)
			fd = (open(file->file, O_RDONLY));
		if (fd < 0)
		{
			printf("%s: No such file or directory\n", file->file);
			return (-1);
		}
		if (file->args != NULL)
			update_in_args(cmd, file);
		file = file->next;
		close(fd);
	}
	if (file->type == REDL)
	{
		if (open(file->file, O_RDONLY) < 0)
		{
			printf("%s: No such file or directory\n", file->file);
			return (-1);
		}
		if (file->args != NULL)
			update_in_args(cmd, file);
		return (open(file->file, O_RDONLY));
	}
	return (0);
}

//check by cmd->output.. -> next.. -> next
//the last output file gets opened and returned.
int	open_files_output(t_cmd *cmd)
{
	int		fd;
	t_rdr	*file;

	file = cmd->output;
	while (file->next != NULL)
	{
		if (file->type == REDR)
			fd = (open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0666));
		else if (file->type == REDRR)
			fd = (open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0666));
		if (fd < 0)
			return (1);
		if (file->args != NULL)
			update_out_args(cmd, file);
		file = file->next;
		close(fd);
	}
	if (file->args != NULL)
		update_out_args(cmd, file);
	if (file->type == REDR)
		return (open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0666));
	else if (file->type == REDRR)
		return (open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0666));
	return (0);
}

//maybe split input/output redir into diff functions
int	redirect(t_cmd *cmd, t_env **env)
{
	pid_t	pid;
	int		fd_in;
	int		fd_out;

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
		if (cmd->output)
		{
			fd_out = open_files_output(cmd);
			if (fd_out < 0)
			{
				printf("error opening file\n");
				return (1);
			}
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
			ft_execs(cmd, env);
		}
		if (cmd->input)
		{
			fd_in = open_files_input(cmd);
			if (fd_in < 0)
				return (1);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
			ft_execs(cmd, env);
		}
		return (0);
	}
	else
	{
		close(fd_out);
		close(fd_in);
		wait(0);
	}
	return (0);
}

int	exec_redir(t_cmd *cmd, t_env **env)
{
	if (redirect(cmd, env) == -1)
	{
		printf("redir fork/dup error\n");
		return (1);
	}
	return (0);
}
