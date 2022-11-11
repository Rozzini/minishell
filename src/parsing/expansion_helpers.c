/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:41:18 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/11 18:45:27 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expansion_freeing(t_env	*temp, t_parsing *prs, char	*temp_s, char *s)
{
	if (temp != NULL && ft_strcmp(temp->key, "?") == 0)
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
}

void	check_if_next_expansion_helper(char *s, t_parsing *prs)
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
}

int	check_if_next_expansion(char *s, t_parsing *prs)
{
	while (s[prs->j] != '\0')
	{
		check_if_next_expansion_helper(s, prs);
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
