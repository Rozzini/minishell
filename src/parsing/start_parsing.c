/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:13:41 by mraspors          #+#    #+#             */
/*   Updated: 2022/08/02 10:20:37 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_separator(char c)
{
	if (c == ' ' || c == 9 || c == 11 || c == '\n')
		return (1);
	return (0);
}

char	*get_tokens_q_iter(char *s, char quote)
{
	s++;
	if (*s == quote)
		return (s);
	while (*s != quote && *s != '\0')
		s++;
	return (s);
}

int	check_expansion_name(char *start, char *end, t_env **env)
{
	char	*name;
	t_env	*temp;

	name = ft_substr(start, 1, ft_strlen(start) - ft_strlen(end));
	temp = find_node_by_key(*env, name);
	free(name);
	if (temp == NULL)
		return (1);
	return (0);
}

char	*iterate_expansion(char	*string)
{
	char	*s;

	s = string;
	while (is_separator(*s) == 0 && *s != '\0')
		s++;
	return (s);
}

void	put_tokens(char *s, t_tokens *toks, t_env **env)
{
	char	c;
	char	*exp_start;
	char	*exp_end;
	char	*name;
	t_env	*temp;
	char	tok[10000];
	int		i;
	int		j;
	int		k;

	k = 0;
	j = 0;
	i = 0;
	toks->args = malloc(sizeof(char *) * toks->arg_c + 1);
	while (*s != '\0')
	{
		j = 0;
		if (is_separator(*s) == 0)
		{
			while (is_separator(*s) == 0 && *s != '\0')
			{
				if (*s == '$')
				{
					exp_start = s;
					exp_end = iterate_expansion(exp_start);
					if (check_expansion_name(exp_start, exp_end, env) == 0)
					{
						k = 0;
						name = ft_substr(exp_start, 1,
								ft_strlen(exp_start) - ft_strlen(exp_end));
						temp = find_node_by_key(*env, name);
						free(name);
						while (temp->val[k] != '\0')
						{
							tok[j] = temp->val[k];
							j++;
							k++;
						}
					}
					s = exp_end;
				}
				if (*s == 34 || *s == 39)
				{
					c = *s;
					s++;
					while (*s != c && *s != '\0')
					{
						if (*s == '$' && c == 34)
						{
							exp_start = s;
							exp_end = iterate_expansion(exp_start);
							if (check_expansion_name(exp_start, exp_end, env) == 0)
							{
								k = 0;
								name = ft_substr(exp_start, 1,
										ft_strlen(exp_start) - ft_strlen(exp_end));
								temp = find_node_by_key(*env, name);
								free(name);
								while (temp->val[k] != '\0')
								{
									tok[j] = temp->val[k];
									j++;
									k++;
								}
							}
							s = exp_end;
						}
						tok[j] = *s;
						j++;
						s++;
					}
				}
				else
				{
					tok[j] = *s;
					j++;
					s++;
				}
			}
			tok[j] = '\0';
			toks->args[i] = ft_strdup(tok);
			i++;
		}
		else if (*s == 34 || *s == 39)
		{
			c = *s;
			s++;
			while (*s != c && *s != '\0')
			{
				if (*s == '$' && c == 34)
				{
					exp_start = s;
					exp_end = iterate_expansion(exp_start);
					if (check_expansion_name(exp_start, exp_end, env) == 0)
					{
						k = 0;
						name = ft_substr(exp_start, 1,
								ft_strlen(exp_start) - ft_strlen(exp_end));
						temp = find_node_by_key(*env, name);
						free(name);
						while (temp->val[k] != '\0')
						{
							tok[j] = temp->val[k];
							j++;
							k++;
						}
					}
					s = exp_end;
				}
				tok[j] = *s;
				j++;
				s++;
			}
			tok[j] = '\0';
			toks->args[i] = ft_strdup(tok);
			i++;
		}
		if (*s == '\0')
			break ;
		s++;
	}
	toks->args[i] = NULL;
}

void	get_tokens(char *string, t_tokens *tokens, t_env **env)
{
	char	*s;

	s = string;
	tokens->arg_c = 0;
	while (*s != '\0')
	{
		if (is_separator(*s) == 0)
		{
			while (is_separator(*s) == 0 && *s != '\0')
			{
				if (*s == 34 || *s == 39)
					s = get_tokens_q_iter(s, *s);
				s++;
			}
			tokens->arg_c++;
		}
		else if (*s == 34 || *s == 39)
		{
			s = get_tokens_q_iter(s, *s);
			s++;
			tokens->arg_c++;
		}
		if (*s == '\0')
			break ;
		s++;
	}
	put_tokens(string, tokens, env);
}

//checks for opened quotes first if everything fine
//splits string and saves each argument and
//also amount of arguments to tokens structure
int	start_parsing(t_tokens *tokens, t_env **env)
{
	if (tokens->cmdl[0] == '\0')
		return (1);
	add_history(tokens->cmdl);
	if (check_q(tokens->cmdl) == 1)
		return (1);
	get_tokens(tokens->cmdl, tokens, env);
	if (tokens->args == NULL)
		return (1);
	//check_expansion(tokens, env);
	return (0);
}
