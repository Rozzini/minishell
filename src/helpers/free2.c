/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:02:24 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/11 18:03:27 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//free_doublptr(t->args);
void	free_token(t_tokens *t)
{
	if (t != NULL)
	{
		if (t->cmdl)
			free(t->cmdl);
		free(t);
	}
}

void	free_list(t_env **list)
{
	t_env	*temp;

	temp = *list;
	while (temp != NULL)
	{
		delete_head(list);
		temp = *list;
	}
}

void	free_parsing(t_parsing *prs)
{
	if (prs->og_token != NULL)
		free(prs->og_token);
	if (prs->token != NULL)
		free(prs->token);
	free_doublptr(prs->exp_name);
	free(prs);
	prs = NULL;
}

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
