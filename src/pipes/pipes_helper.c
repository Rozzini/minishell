/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:47:45 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/22 22:44:27 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#include "../../minishell.h"

void	ft_closer(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->next != NULL)
	{
		if (tmp->fd[0])
			close(tmp->fd[0]);
		if (tmp->fd[1])
			close(tmp->fd[1]);
		tmp = tmp->next;
	}
}

void	close_all_pipes(t_cmd *cmd)
{
	t_cmd	*temp;

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
		close(cmd->fd[1]);
	}
	else if (cmd->next == NULL)
	{
		dup2(prev_fd[0], 0);
		close(prev_fd[1]);
		close(prev_fd[0]);
	}
	else
	{
		dup2(prev_fd[0], 0);
		close(prev_fd[0]);
		close(prev_fd[1]);
		dup2(cmd->fd[1], 1);
		close(cmd->fd[1]);
		close(cmd->fd[0]);
	}
}

void	close_unused_fds(t_cmd *cmd, int counter)
{
	int		i;
	t_cmd	*temp;

	i = 0;
	temp = cmd;
	while (temp->next != NULL)
	{
		if (i != counter && i != counter - 1)
		{
			if (temp->fd[0])
			{
				close(temp->fd[0]);
				temp->fd[0] = 0;
			}
			if (temp->fd[1])
			{
				close(temp->fd[1]);
				temp->fd[1] = 0;
			}
		}
		temp = temp->next;
		i++;
	}
}
