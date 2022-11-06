/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:14:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/06 01:31:14 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	copy_expansion_name(char *s, t_parsing *prs, int i)
{
	int			start;

	i++;
	start = i;
	if (ft_isalpha(s[i]) != 0)
	{
		while (is_separator(s[i]) == 0 && ft_isalnum(s[i]) == 1 && s[i] != '\0')
			i++;
		prs->exp_name[prs->iter] = ft_substr(&s[start], 0,
				ft_strlen(&s[start]) - ft_strlen(&s[i]));
	}
	else if (s[i] == 34 || s[i] == 32)
		prs->exp_name[prs->iter] = NULL;
	else
	{
		i++;
		prs->exp_name[prs->iter] = ft_substr(&s[start], 0,
				ft_strlen(&s[start]) - ft_strlen(&s[i]));
		i--;
	}
	prs->iter++;
	return (i);
}

t_env	*check_expansion_name(char *name, t_env **env)
{
	t_env	*temp;

	if (name == NULL)
		return (NULL);
	if (ft_strcmp(name, "?") == 0)
	{
		temp = malloc(sizeof(t_env));
		temp->key = ft_strdup("?");
		temp->val = ft_itoa(g_signal);
		temp->next = NULL;
		return (temp);
	}
	temp = find_node_by_key(*env, name);
	if (temp == NULL)
		return (NULL);
	return (temp);
}

int	do_expansion_helper(int i, t_parsing *prs, t_env **env)
{
	t_env	*temp;
	char	*temp_s;
	char	*s;

	temp = check_expansion_name(prs->exp_name[prs->c], env);
	temp_s = ft_substr(prs->token, 0,
			ft_strlen(prs->token) - ft_strlen(&(prs->token[i])));
	if (temp != NULL)
	{
		s = ft_strjoin(temp_s, temp->val);
		free(temp_s);
		temp_s = ft_strdup(s);
		free(s);
		s = ft_strjoin(temp_s, &(prs->token[i + 1
					+ ft_strlen(prs->exp_name[prs->c])]));
	}
	else
	s = ft_strjoin(temp_s, &(prs->token[i + 1
					+ ft_strlen(prs->exp_name[prs->c])]));
	if (ft_strcmp(temp->key, "?") == 0)
	{
		free(temp->key);
		free(temp->val);
		free(temp);
	}
	free(temp_s);
	free(prs->token);
	prs->token = ft_strdup(s);
	free(s);
	prs->c++;
	return (i);
}

int	check_if_next_expansion(char *s, t_parsing *prs)
{
	while (s[prs->j] != '\0')
	{
		if (s[prs->j] == 34 && prs->sq == 0)
		{
			if (prs->dq == 0)
				prs->dq = 1;
			else
				prs->dq = 0;
		}
		if (s[prs->j] == 39 && prs->dq == 0)
		{
			if (prs->sq == 0)
				prs->sq = 1;
			else
				prs->sq = 0;
		}
		if (s[prs->j] == '$')
		{
			if (prs->sq == 0)
				return (0);
			else
				return (1);
		}
		prs->j++;
	}
	return (1);
}

void	do_expansion(t_parsing	*prs, t_env **env)
{
	int		i;
	int		do_exp;

	i = 0;
	prs->c = 0;
	prs->j = 0;
	prs->sq = 0;
	prs->dq = 0;
	while (prs->c < prs->iter)
	{
		do_exp = check_if_next_expansion(prs->og_token, prs);
		prs->j++;
		while (prs->token[i] != '$')
		{
			if (prs->token[i] == '\0')
				break ;
			i++;
		}
		if (do_exp == 0)
			do_expansion_helper(i, prs, env);
		else
			i++;
	}
}
