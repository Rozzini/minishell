/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:47:45 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/22 22:26:52 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_closer(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->next != NULL)
	{
		if (tmp->fd[0])
		{
			close(tmp->fd[0]);
			write(2, "clos9\n", 6);
			// tmp->fd[0] = 0;
		}
		if (tmp->fd[1])
		{
			close(tmp->fd[1]);
			write(2, "clo10\n", 6);
			// tmp->fd[1] = 0;
		}
		tmp = tmp->next;
	}
}

void	close_all_pipes(t_cmd *cmd)
{
	t_cmd *temp;
	temp = cmd;
	while (temp->prev != NULL)
	{
		temp = temp->prev;
		if (temp->fd[0])
			close(temp->fd[0]);
		if (temp->fd[1])
			close(temp->fd[1]);
	}
	temp = cmd;
	while (temp->next != NULL)
	{
		temp = temp->next;
		if (temp->fd[0])
			close(temp->fd[0]);
		if (temp->fd[1])
			close(temp->fd[1]);
	}
}

void	ft_dup2(t_cmd *cmd, int *prev_fd)
{
	if (cmd->first_cmd == 1)
	{
		dup2(cmd->fd[1], 1);
		close(cmd->fd[0]);
		write(2, "clos1\n", 6);
		close(cmd->fd[1]);
		write(2, "clos2\n", 6);
	}
	else if (cmd->next == NULL)
	{
		dup2(prev_fd[0], 0);
		close(prev_fd[1]);
		write(2, "clos3\n", 6);
		close(prev_fd[0]);
		write(2, "clos4\n", 6);
	}
	else
	{
		dup2(prev_fd[0], 0);
		close(prev_fd[0]);
		write(2, "clos5\n", 6);
		close(prev_fd[1]);
		write(2, "clos6\n", 6);
		dup2(cmd->fd[1], 1);
		close(cmd->fd[1]);
		write(2, "clos7\n", 6);
		close(cmd->fd[0]);
		write(2, "clos8\n", 6);
	}
	//close_all_pipes(cmd);
}

void	close_unused_fds(t_cmd *cmd, int counter)
{
	int		i;
	t_cmd	*temp;

	i = 0;
	temp = cmd;
	while (temp->next != NULL)
	{
		write(2, "loop\n", 5);
		if (i != counter && i != counter - 1)
		{
			if (temp->fd[0])
			{
				close(temp->fd[0]);
				write(2, "clo00\n", 6);
				temp->fd[0] = 0;
			}
			if (temp->fd[1])
			{
				close(temp->fd[1]);
				write(2, "clo11\n", 6);
				temp->fd[1] = 0;
			}
		}
		temp = temp->next;
		i++;
	}
	write(2, "exit loop\n", 10);
}
