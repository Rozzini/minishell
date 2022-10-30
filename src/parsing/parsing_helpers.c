/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:14:23 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/21 18:50:02 by mraspors         ###   ########.fr       */
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

void	p_inout(t_rdr *rdr)
{
	int		i;
	t_rdr	*temp;

	temp = rdr;
	if (temp == NULL)
	{
		printf("	NO REDIRECIONS\n\n");
		return ;
	}
	while (temp != NULL)
	{
		printf("	FILE: %s\n", temp->file);
		printf("	TYPE: %d\n", temp->type);
		i = 0;
		printf("	RDR ARGS: ");
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
		printf("\n	------------\n");
		temp = temp->next;
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
		printf("\nARGS: ");
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
		printf("ARGC: %d\n\n", temp->arg_c);
		printf("	INPUT REDIRECTIONS\n--------------------------------\n");
		p_inout(temp->input);
		printf("	OUTPUT REDIRECTIONS\n--------------------------------\n");
		p_inout(temp->output);
		temp = temp->next;
		if (temp != NULL)
			printf("\n=====================================\n");
	}
	printf("===================================\n\n");
}
