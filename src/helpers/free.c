/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:11:48 by mraspors          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/21 19:50:57 by mraspors         ###   ########.fr       */
=======
/*   Updated: 2022/10/26 05:16:25 by mraspors         ###   ########.fr       */
>>>>>>> a38892c213958d44ac70d1e921bae6a554d2c134
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
<<<<<<< HEAD
=======
	t_cmd	*del_node;
>>>>>>> a38892c213958d44ac70d1e921bae6a554d2c134

	temp = *head;
	while (temp != NULL)
	{
		free_doublptr(temp->args);
		if (temp->input != NULL)
			free_rdr(&temp->input);
		if (temp->output != NULL)
			free_rdr(&temp->output);
<<<<<<< HEAD
		*head = (*head)->next;
		temp = *head;
=======
		del_node = temp;
		temp = temp->next;
		free(del_node);
>>>>>>> a38892c213958d44ac70d1e921bae6a554d2c134
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
