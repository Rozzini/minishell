/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:47:45 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/12 17:51:17 by mraspors         ###   ########.fr       */
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

void	push_rdr_cpy(t_rdr **head, t_rdr *cmd)
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

void	cur_cmd_cpy_rdr(t_cmd *cmd, t_cmd	*new_node)
{
	t_rdr	*temp;

	temp = cmd->input;
	while (temp != NULL)
	{
		push_rdr_cpy(&new_node->input, temp);
		temp = temp->next;
	}
	temp = cmd->output;
	while (temp != NULL)
	{
		push_rdr_cpy(&new_node->output, temp);
		temp = temp->next;
	}
}

void	cur_cmd_cpy(t_cmd **head_ref, t_cmd *cmd)
{
	t_cmd	*new_node;
	int		i;

	i = 0;
	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->next = NULL;
	new_node->output = NULL;
	new_node->input = NULL;
	new_node->arg_c = cmd->arg_c;
	new_node->first_cmd = 0;
	cur_cmd_cpy_rdr(cmd, new_node);
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
