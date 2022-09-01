/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:13:41 by mraspors          #+#    #+#             */
/*   Updated: 2022/09/01 05:22:22 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_separator(char c)
{
	if (c == 32 || c == 9 || c == 11 || c == '\n')
		return (1);
	return (0);
}

char	*tokens_q_iter(char *s)
{
	char	q;

	q = *s;
	s++;
	if (*s == q)
		return (s);
	while (*s != q && *s != '\0')
		s++;
	return (s);
}

void	save_tokens(char *string, t_tokens *tokens)
{
	char	*s;
	char	*c;
	int		i;

	i = 0;
	s = string;
	tokens->args = malloc(sizeof(char *) * tokens->arg_c + 1);
	while (*s != '\0')
	{
		if (is_separator(*s) == 0)
		{
			c = s;
			while (is_separator(*s) == 0 && *s != '\0')
			{
				if (*s == 34 || *s == 39)
					s = tokens_q_iter(s);
				s++;
			}
			tokens->args[i] = ft_substr(c, 0, ft_strlen(c) - ft_strlen(s));
			i++;
		}
		s++;
	}
	tokens->args[i] = NULL;
}

void	count_tokens(char *string, t_tokens *tokens)
{
	char	*s;

	s = string;
	while (*s != '\0')
	{
		if (is_separator(*s) == 0)
		{
			while (is_separator(*s) == 0 && *s != '\0')
			{
				if (*s == 34 || *s == 39)
					s = tokens_q_iter(s);
				s++;
			}
			tokens->arg_c++;
		}
		s++;
	}
}

//checks for opened quotes first if everything fine
//splits string and saves each argument and
//also amount of arguments to tokens structure
int	start_parsing(t_tokens *tokens, t_env **env, t_cmd **cmd)
{
	if (tokens->cmdl[0] == '\0')
		return (1);
	add_history(tokens->cmdl);
	if (check_q(tokens->cmdl) == 1)
		return (1);
	tokens->arg_c = 0;
	count_tokens(tokens->cmdl, tokens);
	save_tokens(tokens->cmdl, tokens);
	quotes_exp_check(tokens, env);
	if (start_pipes_parsing(tokens, cmd) == 1)
		return (1);
	if (tokens->args == NULL)
		return (1);
	return (0);
}
