/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:35:02 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/14 15:43:14 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_quotes(char *string, t_parsing *prs)
{
	char	c;

	c = *string;
	string++;
	while (*string != c && *string != '\0')
	{
			prs->token[prs->i] = *string;
			prs->i++;
			string++;
	}
}

void	check_quotes(char	*string, t_parsing	*prs)
{
	int		i;

	i = 0;
	while (*string != '\0')
	{
		if (*string == 34 || *string == 39)
		{
			remove_quotes(string, prs);
			string = tokens_q_iter(string);
			string++;
			if (*string == '\0')
				break ;
		}
		else
		{
			prs->token[prs->i] = *string;
			prs->i++;
			string++;
		}
	}
	prs->token[prs->i] = '\0';
}

void	count_possible_expansion(t_parsing *parsing)
void	save_exp_data(char *string, t_parsing *parsing)
{
	int		i;
	char	c;

	i = 0;
	while(string[i] != '\0')
	{
		if (string[i] == 34 || string[i] == 39)
		{
			c = string[i];
			i++;
			while (string[i] != c)
			{
				if (string[i] == '$' && c == 34)
					i = copy_expansion_name(string, parsing, i);
				else
				i++;
			}
			i++;
		}
		else if (string[i] == '$')
			i = copy_expansion_name(string, parsing, i);
		else
			i++;
	}	
}

void	quotes_exp_check(t_tokens *tokens, t_env **env)
{
	t_parsing	*prs;
	int			i;

	i = 0;
	prs = malloc(sizeof(t_parsing));
	while (tokens->args[i] != NULL)
	{
		prs->iter = 0;
		prs->i = 0;
		prs->token = ft_strdup(tokens->args[i]);
		save_exp_data(tokens->args[i], prs);
		prs->exp_name[prs->iter] = NULL;
		do_expansion(prs, env);
		check_quotes(tokens->args[i], prs);
		free(tokens->args[i]);
		tokens->args[i] = prs->token;
		i++;
	}
}
