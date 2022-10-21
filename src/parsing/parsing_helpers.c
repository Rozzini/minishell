/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:14:23 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/20 22:49:29 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_separator(char c)
{
	if (c == 32 || c == 9 || c == 11 || c == '\n')
		return (1);
	return (0);
}

int	is_special(char *s)
{
	if (s[0] == '<' && s[1] == '<')
		return (2);
	else if (s[0] == '>' && s[1] == '>')
		return (2);
	else if (s[0] == '<' || s[0] == '>' || s[0] == '|')
		return (1);
	return (0);
}

int	check_type(char *s)
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

void	p_tokens(t_tokens *tokens)
{
	int	i;

	i = 0;
	printf("\n===================================\n");
	printf("tokens output\n");
	while (tokens->args[i] != NULL)
	{
		printf("[%s]  ", tokens->args[i]);
		i++;
	}
	printf("\ntoken_count: %d\n", tokens->arg_c);
	printf("===================================\n");
}

void	p_in_out_args(char **in, char **out)
{
	int	i;

	i = 0;
	printf("IN_ARGS: ");
	if (in == NULL)
		printf("NULL");
	else
	{
		while (in[i] != NULL)
		{
			printf("[%s] ", in[i]);
			i++;
		}	
	}
	printf("\nOUT_ARGS: ");
	if (out == NULL)
		printf("NULL");
	else
	{
		while (out[i] != NULL)
		{
			printf("[%s] ", out[i]);
			i++;
		}	
	}
	printf("\n\n");
}

void	p_cmd(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;

	i = 0;
	temp = cmd;
	printf("===========cmd struct output=============\n");
	while (temp != NULL)
	{
		i = 0;
		printf("args: ");
		if (temp->args == NULL)
			printf("NULL");
		else
		{
			while (temp->args[i] != NULL)
			{
				printf("[%s] ", temp->args[i]);
				i++;
			}	
		}
		printf("\n");
		printf("INPUT: %s\nOUPUT: %s\nIN TYPE: %d\nOUT TYPE: %d\nARGC: %d\n",
			temp->input, temp->output,
			temp->in_type, temp->out_type, temp->arg_c);
		p_in_out_args(temp->in_args, temp->out_args);
		temp = temp->next;
	}
	printf("===================================\n");
}
