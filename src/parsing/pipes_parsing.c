/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:48:36 by mraspors          #+#    #+#             */
/*   Updated: 2022/09/12 09:46:17 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*find_last(t_cmd **head)
{
	t_cmd	*temp;

	temp = *head;
	if (*head == NULL)
		return (NULL);
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

int		pick_type(char *s)
{
	if (s == NULL)
		return (0);
	if (ft_strcmp(s, "|") == 0)
		return (1);
	if (ft_strcmp(s, ">") == 0)
		return (2);
	if (ft_strcmp(s, ">>") == 0)
		return (3);
	if (ft_strcmp(s, "<") == 0)
		return (4);
	if (ft_strcmp(s, "<<") == 0)
		return (5);
	else
		return (-1);
}

//add new node to list
void	push_cmd(t_cmd **head_ref, char **args, int start, int end)
{
	t_cmd	*last;
	t_cmd	*new_node;
	int		i;

	i = 0;
	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->args = malloc(sizeof(char *) * (end - start + 1));
	while (start < end)
	{
		new_node->args[i] = ft_strdup(args[start]);
		i++;
		start++;
	}
	new_node->args[i] = NULL;
	new_node->arg_c = i;
	new_node->type = pick_type(args[end]);
	new_node->next = NULL;
	last = find_last(head_ref);
	if (*head_ref == NULL)
		*head_ref = new_node;
	else
	last->next = new_node;
	last = *head_ref;
}

void	make_commands(t_tokens *tokens, t_cmd **cmd)
{
	int	i;
	int	start;

	start = 0;
	i = 0;
	while (tokens->args[i] != NULL)
	{
		if (ft_strcmp(tokens->args[i], "|") == 0)
		{
			push_cmd(cmd, tokens->args, start, i);
			start = i + 1;
		}
		i++;
	}
	push_cmd(cmd, tokens->args, start, i);
}

int	start_pipes_parsing(t_tokens *tokens, t_cmd **cmd)
{
	make_commands(tokens, cmd);
	return (0);
}