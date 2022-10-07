/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:48:36 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/07 09:13:02 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	p_tokens(t_tokens *tokens)
{
	int i = 0;

	while(tokens->args[i] != NULL)
	{
		printf("token %d: %s\n", i+1, tokens->args[i]);
		i++;
	}
	printf("args_c: %d\n", tokens->arg_c);
}

void	p_cmd(t_cmd *cmd)
{
	t_cmd *temp;
	int i = 0;
	
	temp = cmd;
	while(temp != NULL)
	{
		i = 0;
		while(temp->args[i] != NULL)
		{
			printf("[%s] ", temp->args[i]);
			i++;
		}
		printf("\n");
		printf("input: %s\noutput: %s\n", temp->input, temp->ouput);
		printf("\n\n");
		temp = temp->next;
	}
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
	//t_cmd	*last;
	t_cmd	*new_node;
	int		i;

	i = 0;
	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->args = malloc(sizeof(char *) * (tokens->end - tokens->start + 1));
	while (token->start < tokens->end)
	{
		new_node->args[i] = ft_strdup(tokens->args[tokens->start]);
		i++;
		tokens->start++;
	}
	new_node->args[i] = NULL;
	new_node->arg_c = i;
	new_node->next = *head_ref;
	new_node->ouput = NULL;
	new_node->input = NULL;
	*head_ref = new_node;
	tokens->last = new_node;
	//last = find_last(head_ref);
	// if (*head_ref == NULL)
	// 	*head_ref = new_node;
	// else
	// last->next = new_node;
	// last = *head_ref;
}

char	**malloc_realloc_for_redir(char **str, int len)
{
	char	**s;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str == NULL)
	{
		s = malloc(sizeof(char *) * (len + 1));
		return (s);
	}
	while (str[i] != NULL)
		i++;
	s = malloc(sizeof(char *) * (i + len + 1));
	i = 0;
	while (str[i] != NULL)
	{
		s[i] = ft_strdup(str[i]);
		i++;
	}
	s[i] = NULL;
	free_doublptr(str);
	return (s);
}

char	**choose_redirection_type(int type, t_cmd *cmd)
{
	if (type == 1)
		return (cmd->ouput);
	if (type == 2)
		return (cmd->ouput);
	if (type == 3)
		return (cmd->input);
	if (type == 4)
		return (cmd->input);
	return (NULL);
}

void	cmd_add_redirection(t_tokens *tokens, t_cmd *cmd, int type)
{
	int		i;
	char	**args;

	i = 0;
	args = choose_redirection_type(type, cmd);
	args = malloc_realloc_for_redir(args, tokens->end - tokens->start);
	while (args[i] != NULL)
		i++;
	while (token->start < tokens->end)
	{
		args[i] = ft_strdup(tokens->args[tokens->start]);
		i++;
		tokens->start++;
	}
	args[i] = NULL;
}

int		check_type(char *s)
{
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
	return (-1);
}

void	make_commands(t_tokens *tokens, t_cmd **cmd)
{
	int	i;
	int	type;

	tokens->start = 0;
	i = 0;
	while (tokens->args[i] != NULL)
	{
		type = check_type(tokens->args[i]);
		if (type == 0)
		{
			tokens->end = i;
			push_cmd(cmd, tokens);
			tokens->start = i + 1;
		}
		else if (type == 1)
		{
			tokens->end = i;
			cmd_add_redirection(tokens, tokens->last, type);
			tokens->start = i + 1;
		}
		else if (type == 2)
		{
			tokens->end = i;
			cmd_add_redirection(tokens, tokens->last, type);
			tokens->start = i + 1;
		}
		else if (type == 3)
		{
			tokens->end = i;
			cmd_add_redirection(tokens, tokens->last, type);
			tokens->start = i + 1;
		}
		else if (type == 4)
		{
			tokens->end = i;
			cmd_add_redirection(tokens, tokens->last, type);
			tokens->start = i + 1;
		}
		i++;
	}
	push_cmd(cmd, tokens);
}


int	start_pipes_parsing(t_tokens *tokens, t_cmd **cmd)
{
	p_tokens(tokens);
	make_commands(tokens, cmd);
	printf("\n\n");
	p_cmd(*cmd);
	return (0);
}
