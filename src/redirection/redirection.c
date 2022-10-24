/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:22:37 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/24 12:37:24 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//-------------
int	ft_2d_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}


void update_out_args(t_cmd *cmd, t_rdr *file)
{
	char	**og_args;
	char	**io_args;
	int		i;
	int		j;

	if (cmd->output->args[0] == NULL)
		return ;
	og_args = cmd->args;
	io_args = file->args;
	i = 0;
	j = 0;
	cmd->args = malloc(sizeof(char *) * (ft_2d_size(cmd->args) + ft_2d_size(cmd->output->args) + 1));
	while (og_args[i])
	{
		cmd->args[i] = ft_strdup(og_args[i]);
		// printf("[%d]: %s\n",i, cmd->args[i]);
		i++;
	}
	while (io_args[j])
	{
		cmd->args[i] = ft_strdup(io_args[j]);
		// printf("[%d]: %s\n",i, cmd->args[i]);
		j++;
		i++;
	}
	cmd->args[i] = NULL;
	cmd->arg_c = i;
	free_doublptr(io_args);
	free_doublptr(og_args);
}

void update_in_args(t_cmd *cmd, t_rdr *file)
{
	char	**og_args;
	char	**io_args;
	int 	i;
	int 	j;

	if (cmd->input->args[0] == NULL)
		return ;
	og_args = cmd->args;
	io_args = file->args;
	i = 0;
	j = 0;
	cmd->args = malloc(sizeof(char *) * (ft_2d_size(cmd->args) + ft_2d_size(cmd->input->args) + 1));
	//printf("size: %d\n", ft_2d_size(cmd->args) + ft_2d_size(cmd->input->args));
	printf("%s\n", og_args[0]);
	while (og_args[i])
	{
		cmd->args[i] = ft_strdup(og_args[i]);
		// printf("[%d]: %s\n",i, cmd->args[i]);
		i++;
	}
	j = 0;
	while (io_args[j])
	{
		cmd->args[i] = ft_strdup(io_args[j]);
		// printf("[%d]: %s\n",i, cmd->args[i]);
		j++;
		i++;
	}
	cmd->args[i] = NULL;
	cmd->arg_c = i;
	free_doublptr(io_args);
	free_doublptr(og_args);
}
//----------------


//gotta read from file
int open_files_input(t_cmd *cmd)
{
	int fd;
	t_rdr *file;

	file = cmd->input;
	while (file->next != NULL)
	{
		if (file->type == REDL)
			fd = (open(file->file, O_RDONLY));
		if (fd < 0)
		{
			printf("%s: No such file or directory\n", file->file); //make it >
			return (-1);
		}
		update_in_args(cmd, file);
		file = file->next;
		close(fd);
	}
	if (file->type == REDL)
	{
		if (open(file->file, O_RDONLY) < 0)
		{
			printf("%s: No such file or directory\n", file->file); //make it >
			return (-1);
		}
		update_in_args(cmd, file);
		return (open(file->file, O_RDONLY));
	}
	// else if (file->type == HEREDOC)
	// 	return (open(file->file));
	return (0);
}


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
		// if (fd < 0)
		// 	return (1);
		update_out_args(cmd, file);
		file = file->next;
		close(fd);
	}
	update_out_args(cmd, file);
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
			return (ft_execs(cmd, env, path));
		}
		if (cmd->input)
		{
			fd_in = open_files_input(cmd);
			if (fd_in < 0)
				return (1);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
			return(ft_execs(cmd, env, path)); ////pass all the args from each file node to execve 
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

int exec_redir(t_cmd *cmd, t_env **env, char **path)
{
	if (redirect(cmd, env, path) == -1)
	{
		printf("redir fork/dup error\n");
		return (1);
	}
	// 	curr_cmd = curr_cmd->next;
	// }
	return (0);
}