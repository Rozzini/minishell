/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:13:41 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/20 23:16:48 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	count_tokens(char *string, t_tokens *tokens)
{
	char	*s;
	char	*c;
	int		special;

	s = string;
	while (*s != '\0')
	{
		if (is_separator(*s) == 0)
		{
			c = s;
			s = count_save_tokens_iteration(&special, s);
			if (special != 0)
			{
				if (c != s)
					tokens->arg_c++;
				s += special - 1;
			}
			tokens->arg_c++;
			if (*s == '\0')
				break ;
		}
		s++;
	}
}

void	save_tokens(char *string, t_tokens *tokens, int i)
{
	char	*s;
	char	*c;
	int		special;

	s = string;
	while (*s != '\0')
	{
		if (is_separator(*s) == 0)
		{
			c = s;
			s = count_save_tokens_iteration(&special, s);
			if (special != 0)
			{
				if (c != s)
					tokens->args[i++] = ft_substr(c, 0,
							ft_strlen(c) - ft_strlen(s));
				c = s;
				s += special;
			}
			tokens->args[i++] = ft_substr(c, 0, ft_strlen(c) - ft_strlen(s--));
		}
		if (*s != '\0')
			s++;
	}
}

int	check_tokens_validity_helper(t_tokens *tokens, int i)
{
	if (check_type(tokens->args[i]) == 0)
	{
		if (check_type(tokens->args[i + 1]) == 0)
		{
			printf("syntax error near unexpected token `|'\n");
			return (1);
		}
	}
	if (check_type(tokens->args[i]) > 0 && check_type(tokens->args[i]) < 5)
	{
		if (check_type(tokens->args[i + 1]) != 5)
		{
			printf("syntax error near unexpected token `%s'\n", tokens->args[i]);
			return (1);
		}
	}
	return (0);
}

int	check_tokens_validity(t_tokens *tokens)
{
	int	i;

	i = 0;
	if (check_type(tokens->args[0]) == 0
		|| check_type(tokens->args[tokens->arg_c - 1]) != 5)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	while (tokens->args[i] != NULL)
	{
		if (check_tokens_validity_helper(tokens, i) == 1)
			return (1);
		i++;
	}
	return (0);
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
	{
		free(tokens->cmdl);
		free(tokens);
		return (1);
	}
	tokens->arg_c = 0;
	count_tokens(tokens->cmdl, tokens);
	tokens->args = malloc(sizeof(char *) * (tokens->arg_c + 1));
	save_tokens(tokens->cmdl, tokens, 0);
	tokens->args[tokens->arg_c] = NULL;
	quotes_exp_check(tokens, env);
	if (check_tokens_validity(tokens) == 1)
	{
		free_for_start_parsing(tokens);
		return (1);
	}
	start_pipes_parsing(tokens, cmd);
	free_for_start_parsing(tokens);
	return (0);
}
