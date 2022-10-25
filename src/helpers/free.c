/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:11:48 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/25 02:24:37 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_doublptr(char **s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != NULL)
		free(s[i++]);
	free(s);
	s = NULL;
}

void	free_rdr(t_rdr **rdr)
{
	t_rdr	*temp;

	temp = *rdr;
	while (temp != NULL)
	{
		if (temp->file != NULL)
			free (temp->file);
		free_doublptr(temp->args);
		*rdr = (*rdr)->next;
		temp = *rdr;
	}
	free(temp);
	rdr = NULL;
}

void	free_cmd(t_cmd **head)
{
	t_cmd	*temp;

	temp = *head;
	while (temp != NULL)
	{
		free_doublptr(temp->args);
		if (temp->input != NULL)
			free_rdr(&temp->input);
		if (temp->output != NULL)
			free_rdr(&temp->output);
		//free(temp);
		*head = (*head)->next;
		temp = *head;
	}
	free(temp);
	*head = NULL;
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
	if (prs->s != NULL)
		free(prs->s);
	if (prs->token != NULL)
		free(prs->token);
	free_doublptr(prs->exp_name);
	free(prs);
	prs = NULL;
}
