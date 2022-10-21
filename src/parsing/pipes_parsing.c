/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:48:36 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/20 22:50:37 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	push_cmd_init_data(t_cmd *new_node, t_tokens *tokens)
{
	int	i;

	i = 0;
	if (tokens->end - tokens->start != 0)
	{
		new_node->args = malloc(sizeof(char *) * (tokens->end - tokens->start + 1));
		while (tokens->start < tokens->end)
		{
		new_node->args[i++] = ft_strdup(tokens->args[tokens->start]);
		tokens->start++;
		}
		new_node->args[i] = NULL;
	}
	else
		new_node->args = NULL;
	new_node->arg_c = i;
	new_node->next = NULL;
	new_node->output = NULL;
	new_node->input = NULL;
	new_node->in_args = NULL;
	new_node->out_args = NULL;
	new_node->in_type = 0;
	new_node->out_type = 0;
}

//add new node to list
void	push_cmd(t_cmd **head_ref, t_tokens *tokens)
{
	t_cmd	*last;
	t_cmd	*new_node;
	int		i;

	i = 0;
	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	push_cmd_init_data(new_node, tokens);
	tokens->last = new_node;
	last = find_last(head_ref);
	if (*head_ref == NULL)
		*head_ref = new_node;
	else
	last->next = new_node;
}

void	cmd_add_redirection(t_tokens *tokens, t_cmd *cmd, int type)
{
	char	*arg;
	int		i;

	arg = ft_strdup(tokens->args[tokens->start]);
	if (type == 1 || type == 2)
	{
		if (cmd->output != NULL)
			free (cmd->output);
		cmd->output = arg;
		cmd->out_type = type;
		if (tokens->end - ++tokens->start > 0)
		{
			i = 0;
			cmd->out_args = malloc(sizeof(char *) * (tokens->end - tokens->start + 1));
			while (tokens->start < tokens->end)
			{
				cmd->out_args[i++] = ft_strdup(tokens->args[tokens->start]);
				tokens->start++;
			}
			cmd->args[i] = NULL;
		}
	}
	else
	{
		if (cmd->input != NULL)
			free (cmd->input);
		cmd->input = arg;
		cmd->in_type = type;
		if (tokens->end - ++tokens->start > 0)
		{
			i = 0;
			cmd->in_args = malloc(sizeof(char *) * (tokens->end - tokens->start + 1));
			while (tokens->start < tokens->end)
			{
				cmd->in_args[i++] = ft_strdup(tokens->args[tokens->start]);
				tokens->start++;
			}
			cmd->args[i] = NULL;
		}
	}
}

//will save first command to cmd
//returns 1 if there is smthing left in tokens->args
//return 0 if there is only 1 command
int	save_first_cmd(t_tokens *tokens, t_cmd **cmd)
{
	int	i;

	i = 0;
	tokens->start = 0;
	while (tokens->args[i] != NULL)
	{
		if (check_type(tokens->args[i]) != 5)
		{
			tokens->end = i;
			push_cmd(cmd, tokens);
			tokens->last = *cmd;
			tokens->start = i;
			return (1);
		}
		i++;
	}
	tokens->end = i;
	push_cmd(cmd, tokens);
	return (0);
}

void	make_commands(t_tokens *tokens, t_cmd **cmd)
{
	int	i;
	int	type;

	i = tokens->start;
	while (tokens->args[i] != NULL)
	{
		type = check_type(tokens->args[i]);
		i++;
		tokens->start++;
		while (check_type(tokens->args[i]) == 5)
			i++;
		tokens->end = i;
		if (type == 0)
			push_cmd(cmd, tokens);
		else
			cmd_add_redirection(tokens, tokens->last, type);
		tokens->start = i;
	}
}

int	start_pipes_parsing(t_tokens *tokens, t_cmd **cmd)
{
	p_tokens(tokens);
	if (save_first_cmd(tokens, cmd) == 0)
		return (0);
	make_commands(tokens, cmd);
	printf("\n\n");
	p_cmd(*cmd);
	return (0);
}
