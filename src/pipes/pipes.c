/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:37:03 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/11 15:16:03 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_rdr	*find_last_rdr_p(t_rdr *head)
{
	t_rdr	*temp;

	temp = head;
	if (head == NULL)
		return (NULL);
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	push_rdr_p(t_rdr **head, t_rdr *cmd)
{
	t_rdr	*last;
	t_rdr	*new_node;
	int		i;

	i = 0;
	new_node = (t_rdr *)malloc(sizeof(t_rdr));
	new_node->file = ft_strdup(cmd->file);
	new_node->type = cmd->type;
	new_node->next = NULL;
	new_node->next = NULL;
	while (cmd->args[i] != NULL)
		i++;
	new_node->args = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (cmd->args[i] != NULL)
	{
		new_node->args[i] = ft_strdup(cmd->args[i]);
		i++;
	}
	new_node->args[i] = NULL;
	last = find_last_rdr_p(*head);
	if (*head == NULL)
		*head = new_node;
	else
	last->next = new_node;
}

void	push_cmd_p(t_cmd **head_ref, t_cmd *cmd)
{
	t_cmd	*new_node;
	t_rdr	*temp;
	int		i;

	 i = 0;
	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->next = NULL;
	new_node->output = NULL;
	new_node->input = NULL;
	temp = cmd->input;
	while (temp != NULL)
	{
		push_rdr_p(&new_node->input, temp);
		temp = temp->next;
	}
	temp = cmd->output;
	while (temp != NULL)
	{
		push_rdr_p(&new_node->output, temp);
		temp = temp->next;
	}
	new_node->arg_c = cmd->arg_c;
	new_node->args = malloc(sizeof(char *) * (cmd->arg_c + 1));
	while (cmd->args[i] != NULL)
	{
		new_node->args[i] = ft_strdup(cmd->args[i]);
		i++;
	}
	new_node->args[i] = NULL;
	*head_ref = new_node;
}

void	ft_closer(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->next != NULL)
	{
		if (tmp->fd[0] != 0)
		{
			close(tmp->fd[0]);
			tmp->fd[0] = 0;
		}
		if (tmp->fd[1] != 0)
		{
			close(tmp->fd[1]);
			tmp->fd[1] = 0;
		}
		tmp = tmp->next;
	}
}

void	ft_dup2(t_cmd *cmd, int *prev_fd, int flag)
{
	if (flag == 0)
	{
		dup2(cmd->fd[1], 1);
		close(cmd->fd[1]);
		close(cmd->fd[0]);
	}
	else if (cmd->next == NULL)
	{
		dup2(prev_fd[0], 0);
		close(prev_fd[0]);
		close(prev_fd[1]);
	}
	else
	{
		dup2(prev_fd[0], 0);
		dup2(cmd->fd[1], 1);
		close(prev_fd[1]);
		close(prev_fd[0]);
		close(cmd->fd[1]);
		close(cmd->fd[0]);
	}
}

void	exec_pipes(t_cmd *cmd, t_env **env)
{
	t_cmd	*temp;
	t_cmd	*node;
	int		*prev_fd;
	int		i;

	temp = cmd;
	while (temp->next != NULL)
	{
		if (pipe(temp->fd) < 0)
		{
			printf("piping error\n");
			return ;
		}
		temp = temp->next;
	}
	temp = cmd;
	i = 0;
	prev_fd = NULL;
	while (temp != NULL)
	{
		temp->pid = fork();
		if (temp->pid < 0)
			return ;
		if (temp->pid == 0)
		{
			ft_dup2(temp, prev_fd, i);
			push_cmd_p(&node, temp);
			free_cmd(&cmd);
			if (try_parent_builtins(node, env) == 1)
				exit (g_signal);
			if (node->input || node->output)
				exec_redir(node, env);
			else
				ft_execs(node, env);
			exit(g_signal);
		}
		prev_fd = temp->fd;
		temp = temp->next;
		i++;
	}
	ft_closer(cmd);
	temp = cmd;
	while (temp != NULL)
	{
		waitpid(temp->pid, &g_signal, 0);
		temp = temp->next;
	}
}
