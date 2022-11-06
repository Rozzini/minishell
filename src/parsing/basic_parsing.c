/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:35:02 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/05 07:38:24 by mraspors         ###   ########.fr       */
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

void	save_exp_data(char *string, t_parsing *parsing)
{
	int		i;
	char	c;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == 34 || string[i] == 39)
		{
			c = string[i];
			i++;
			while (string[i] != c)
			{
				if (string[i] == '$' && c == 34
					&& string[i + 1] != c && string[i + 1] > 32)
					i = copy_expansion_name(string, parsing, i);
				else
				i++;
			}
			i++;
		}
		else if (string[i] == '$' && string[i + 1] != '\0')
			i = copy_expansion_name(string, parsing, i);
		else
			i++;
	}	
}

int	exp_count(char	*s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '$')
			c++;
		i++;
	}
	return (c);
}

void	quotes_exp_check(t_tokens *tokens, t_env **env)
{
	t_parsing	*prs;
	int			i;

	i = 0;
	while (tokens->args[i] != NULL)
	{
		prs = malloc(sizeof(t_parsing));
		prs->og_token = ft_strdup(tokens->args[i]);
		prs->token = ft_strdup(tokens->args[i]);
		prs->exp_name = malloc(sizeof(char *) * (exp_count(prs->og_token) + 1));
		prs->exp_name[0] = NULL;
		prs->iter = 0;
		prs->i = 0;
		save_exp_data(tokens->args[i], prs);
		prs->exp_name[prs->iter] = NULL;
		check_quotes(tokens->args[i], prs);
		do_expansion(prs, env);
		free(tokens->args[i]);
		tokens->args[i] = ft_strdup(prs->token);
		free_parsing(prs);
		i++;
	}
}
