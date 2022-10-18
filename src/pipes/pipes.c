/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:37:03 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/18 20:37:17 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	make_baby_pipe(int *fd, t_cmd *cmd, char **path, t_env **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (fd[0] != 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		if (fd[1] != 1)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		return (ft_execs(cmd, env, path));
	}
	return (pid);
}

void	exec_pipes(t_cmd *cmd, t_env **env, char **path)
{
	int		fd[2];
	int		prev_fd;
	int		i;
	pid_t	pid;
	t_cmd	*curr_cmd;

	prev_fd = 0;
	i = 1;
	curr_cmd = cmd;
	while (curr_cmd->next != NULL)
	{
		pipe(fd);
		pid = make_baby_pipe(fd, curr_cmd, path, env);
		if (pid == -1)
			return ;
		close(fd[1]);
		prev_fd = fd[0];
		curr_cmd = curr_cmd->next;
		i++;
	}
	if (prev_fd != 0)
		dup2(prev_fd, 0);
	ft_execs(curr_cmd, env, path);
}
