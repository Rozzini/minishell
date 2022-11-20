/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:22:37 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/20 21:21:25 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//gotta read from file
int open_files_input(t_cmd *cmd)
{
	int fd;
	t_rdr *file;

	file = cmd->input;
	if (file == NULL)
		return -2;
	while (file->next != NULL)
	{
		fd = open(file->file, O_RDONLY);
		if (fd < 0)
			return (er_rdr_no_file(file->file));
		file = file->next;
		close(fd);
	}
	fd = open(file->file, O_RDONLY);
	if (fd < 0)
		return (er_rdr_no_file(file->file));
	return (fd);
}

int open_files_output(t_cmd *cmd)
{
	int fd;
	t_rdr *file;

	file = cmd->output;
	if (file == NULL)
		return -2;
	while (file->next != NULL)
	{
		if (file->type == REDR)
			fd = (open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0666)); //O_TRUNC delete past shit
		else if (file->type == REDRR)
			fd = (open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0666));
		if (fd < 0)
			return (1);
		file = file->next;
		close(fd);
	}
	if (file->type == REDR)
		return (open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0666));
	else if (file->type == REDRR)
		return (open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0666));
	return (0);
}

//maybe split input/output redir into diff functions
int redirect(t_cmd *cmd, t_env **env)
{
	g_global.fd_out = open_files_output(cmd);
	g_global.fd_in = open_files_input(cmd);
	if (g_global.fd_out != -2)
	{
		if (dup2(g_global.fd_out, STDOUT_FILENO) == -1)
			return (-1);
		close(g_global.fd_out);
	}
	if (g_global.fd_in != -2)
	{
		if (cmd->input->type == PREPPED_HEREDOC)
			unlink(cmd->input->file);
		if (dup2(g_global.fd_in, STDIN_FILENO) == -1)
			return (-1);
		close(g_global.fd_in);
	}
	if (try_parent_builtins(cmd, env) == 1)
	{
		while (cmd->prev != NULL)
			cmd = cmd->prev;
		free_cmd(&cmd);
		free_list(env);
	}
	ft_execs(cmd, env);
	return (0);
}

void exec_redir(t_cmd *cmd, t_env **env)
{
	if (redirect(cmd, env) == -1)
	{
		free_cmd(&cmd);
		free_list(env);
		exit (1);
	}
}