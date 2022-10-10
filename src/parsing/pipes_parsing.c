/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:48:36 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/10 22:26:02 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	p_tokens(t_tokens *tokens)
{
	int i = 0;
	printf("\n===================================\n");
	printf("tokens output\n");
	while(tokens->args[i] != NULL)
	{
		printf("[%s]  ", tokens->args[i]);
		i++;
	}
	printf("\ntoken_count: %d\n", tokens->arg_c);
}

void	p_cmd(t_cmd *cmd)
{
	t_cmd *temp;
	int i = 0;
	
	temp = cmd;
	printf("cmd struct output\n");
	while(temp != NULL)
	{
		i = 0;
		while(temp->args[i] != NULL)
		{
			printf("[%s] ", temp->args[i]);
			i++;
		}
		printf("\n");
		printf("input: %s\noutput: %s\nin type: %d\nout type: %d\n", temp->input, temp->output, temp->in_type, temp->out_type);
		temp = temp->next;
	}
	printf("===================================\n");
}

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

//add new node to list
void	push_cmd(t_cmd **head_ref, t_tokens *tokens)
{
	t_cmd	*last;
	t_cmd	*new_node;
	int		i;

	i = 0;
	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->args = malloc(sizeof(char *) * (tokens->end - tokens->start + 1));
	while (tokens->start < tokens->end)
	{
		new_node->args[i] = ft_strdup(tokens->args[tokens->start]);
		i++;
		tokens->start++;
	}
	new_node->args[i] = NULL;
	new_node->arg_c = i;
	new_node->next = NULL;
	new_node->output = NULL;
	new_node->input = NULL;
	new_node->in_type = 0;
	new_node->out_type = 0;
	last = find_last(head_ref);
	if (*head_ref == NULL)
		*head_ref = new_node;
	else
	last->next = new_node;
	last = *head_ref;
}

void	cmd_add_redirection(t_tokens *tokens, t_cmd *cmd, int type)
{
	char	*arg;

	arg = ft_strdup(tokens->args[tokens->start]);
	if (type == 1 || type == 2)
	{
		if (cmd->output != NULL)
			free (cmd->output);
		cmd->output = arg;
		cmd->out_type = type;
	}
	else
	{
		if (cmd->input != NULL)
			free (cmd->input);
		cmd->input = arg;
		cmd->in_type = type;
	}
}

int		check_type(char *s)
{
	if (s == NULL)
		return (-1);
	if (ft_strcmp(s, "|") == 0)
		return (0);
	if (ft_strcmp(s, ">") == 0)
		return (1);
	if (ft_strcmp(s, ">>") == 0)
		return (2);
	if (ft_strcmp(s, "<") == 0)
		return (3);
	if (ft_strcmp(s, "<<") == 0)
		return (4);
	return (5);
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
		if(check_type(tokens->args[i]) != 5)
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

	if(save_first_cmd(tokens, cmd) == 0)
		return ;
	i = tokens->start;
	while (tokens->args[i] != NULL)
	{
		type = check_type(tokens->args[i]);
		if (type == 0)
		{
			i++;
			tokens->start++;
			while (check_type(tokens->args[i]) == 5)
				i++;
			tokens->end = i;
			push_cmd(cmd, tokens);
			tokens->start = i;
		}
		else if (type >= 1 && type <= 4)
		{
			i++;
			tokens->start++;
			while (check_type(tokens->args[i]) == 5)
				i++;
			tokens->end = i;
			cmd_add_redirection(tokens, tokens->last, type);
			tokens->start = i;
		}
	}
}


int	start_pipes_parsing(t_tokens *tokens, t_cmd **cmd)
{
	p_tokens(tokens);
	make_commands(tokens, cmd);
	printf("\n\n");
	p_cmd(*cmd);
	return (0);
}
