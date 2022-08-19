/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:35:02 by mraspors          #+#    #+#             */
/*   Updated: 2022/08/19 16:36:43 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_quotes(char *string, t_parsing *prs, int *i)
{
	char	c;

	c = *string;
	string++;
	while (*string != c && *string != '\0')
	{
		if (*string == '$' && c == 34)
		{
			prs->token[prs->i] = *string;
			prs->expansions_p[*i] = prs->i;
			prs->i++;
			string = copy_expansion_name(string, prs, *i);
			*i = *i + 1;
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
}

char	*check_quotes_if_ext(char	*string, t_parsing	*prs, int *i)
{
	prs->token[prs->i] = *string;
	prs->expansions_p[*i] = prs->i;
	prs->i++;
	string = copy_expansion_name(string, prs, *i);
	*i = *i + 1;
	return (string);
}

void	check_quotes(char	*string, t_parsing	*prs)
{
	int		i;

	i = 0;
	while (*string != '\0')
	{
		if (*string == 34 || *string == 39)
		{
			remove_quotes(string, prs, &i);
			string = tokens_q_iter(string);
			string++;
			if (*string == '\0')
				break ;
		}
		else if (*string == '$')
			string = check_quotes_if_ext(string, prs, &i);
		else
		{
			prs->token[prs->i] = *string;
			prs->i++;
			string++;
		}
	}
	prs->token[prs->i] = '\0';
	prs->expansions_p[i] = -1;
}

void	quotes_exp_check(t_tokens *tokens, t_env **env)
{
	t_parsing	*prs;
	int			i;

	count_nodes(env);
	i = 0;
	while (tokens->args[i] != NULL)
	{
		prs = malloc(sizeof(t_parsing));
		prs->i = 0;
		prs->token = malloc(sizeof(char) * (ft_strlen(tokens->args[i]) + 1));
		check_quotes(tokens->args[i], prs);
		do_expansion(prs, env);
		free(tokens->args[i]);
		tokens->args[i] = prs->token;
		i++;
	}
}
