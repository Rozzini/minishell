/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:14:23 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/21 22:13:13 by mraspors         ###   ########.fr       */
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
	int	len;

	len = ft_strlen(s);
	if (s == NULL)
		return (-1);
	if (len == 1)
	{
		if (ft_strcmp(s, "|") == 0)
			return (0);
		if (ft_strcmp(s, ">") == 0)
			return (1);
		if (ft_strcmp(s, "<") == 0)
			return (3);
		else
			return (5);
	}
	if (ft_strcmp(s, ">>") == 0)
		return (2);
	if (ft_strcmp(s, "<<") == 0)
		return (4);
	return (5);
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

char	*count_save_tokens_iteration(int *special, char *s)
{
	while (is_separator(*s) == 0 && *s != '\0')
	{
		*special = is_special(s);
		if (*special != 0)
			break ;
		if (*s == 34 || *s == 39)
			s = tokens_q_iter(s);
		s++;
	}
	return (s);
}
