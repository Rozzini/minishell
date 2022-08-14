/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:14:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/08/14 16:08:07 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_expansion_pointers(t_parsing *prs)
{
	int	i;

	i = 0;
	while (prs->expansions_p[i] != -1)
		i++;
	return (i);
}

char	*copy_expansion_name(char *s, t_parsing *prs, int i)
{
	char	*start;

	s++;
	start = s;
	while (is_separator(*s) == 0 && *s != '\0' && *s != 34)
		s++;
	prs->exp_name[i] = ft_substr(start, 0, ft_strlen(start) - ft_strlen(s));
	return (s);
}

t_env	*check_expansion_name(char *name, t_env **env)
{
	t_env	*temp;

	temp = find_node_by_key(*env, name);
	if (temp == NULL)
		return (NULL);
	return (temp);
}

void	do_extension(t_parsing	*prs, t_env **env)
{
	int		i;
	int		pointer;
	char	*s;
	t_env	*temp;

	i = count_expansion_pointers(prs) - 1;
	while (i >= 0)
	{
		temp = check_expansion_name(prs->exp_name[i], env);
		if (temp != NULL)
		{
			pointer = prs->expansions_p[i];
			s = ft_substr(prs->token, 0,
					ft_strlen(prs->token) - ft_strlen(&(prs->token[pointer])));
			s = ft_strjoin(s, temp->val);
			pointer = prs->expansions_p[i] + 1;
			s = ft_strjoin(s, &(prs->token[pointer]));
			free(prs->token);
			prs->token = s;
		}
		else
		{
			pointer = prs->expansions_p[i];
			s = ft_substr(prs->token, 0,
					ft_strlen(prs->token) - ft_strlen(&(prs->token[pointer])));
			pointer = prs->expansions_p[i] + 1;
			s = ft_strjoin(s, &(prs->token[pointer]));
			free(prs->token);
			prs->token = s;
		}
		i--;
	}
}

void	remove_quotes_if_quotes(char *string, t_parsing *prs, int *i)
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

void	remove_quotes(char	*string, t_parsing	*prs)
{
	int		i;

	i = 0;
	while (*string != '\0')
	{
		if (*string == 34 || *string == 39)
		{
			remove_quotes_if_quotes(string, prs, &i);
			string = tokens_q_iter(string);
			string++;
			if (*string == '\0')
				break ;
		}
		else if (*string == '$')
		{
			prs->token[prs->i] = *string;
			prs->expansions_p[i] = prs->i;
			prs->i++;
			string = copy_expansion_name(string, prs, i);
			i++;
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
		remove_quotes(tokens->args[i], prs);
		do_extension(prs, env);
		free(tokens->args[i]);
		tokens->args[i] = prs->token;
		i++;
	}
}
