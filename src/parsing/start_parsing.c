/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:13:41 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/31 23:48:46 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_tokens_check_sep(char c)
{
	if (c == ' ' || c == 9 || c == 11 || c == '\n')
		return (1);
	return (0);
}

char	*get_tokens_q_iter(char *s, char quote)
{
	if (*s == quote)
	{
		s++;
		while (*s != quote && *s != '\0')
			s++;
	}
	return (s);
}

//export a b c
//p = a
//q = "
void	put_tokens(char *s, t_tokens *toks)
{
	char	c;
	char	tok[10000];
	int		i;
	int		j;

	j = 0;
	i = 0;
	toks->args = malloc(sizeof(char *) * toks->arg_c + 1);
	while (*s != '\0')
	{
		j = 0;
		if (get_tokens_check_sep(*s) == 0)
		{
			while (get_tokens_check_sep(*s) == 0 && *s != '\0')
			{
				if (*s == 34 || *s == 39)
				{
					c = *s;
					s++;
					while (*s != c && *s != '\0')
					{
						tok[j] = *s;
						j++;
						s++;
					}
					if (*s != '\0')
						s++;
				}
				tok[j] = *s;
				j++;
				s++;
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

void	get_tokens(char *string, t_tokens *tokens)
{
	char	*s;

	s = string;
	tokens->arg_c = 0;
	while (*s != '\0')
	{
		if (get_tokens_check_sep(*s) == 0)
		{
			while (get_tokens_check_sep(*s) == 0 && *s != '\0')
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
	put_tokens(string, tokens);
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
	get_tokens(tokens->cmdl, tokens);
	if (tokens->args == NULL)
		return (1);
	count_nodes(env);
	return (0);
}
