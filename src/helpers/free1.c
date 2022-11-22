/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:11:48 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/20 21:55:29 by mraspors         ###   ########.fr       */
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
	t_rdr	*del_node;

	temp = *rdr;
	while (temp != NULL)
	{
		if (temp->file != NULL)
			free (temp->file);
		free_doublptr(temp->args);
		del_node = temp;
		temp = temp->next;
		free(del_node);
	}
	free(temp);
	rdr = NULL;
}

void	free_cmd(t_cmd **head)
{
	t_cmd	*temp;
	t_cmd	*del_node;

	temp = *head;
	while (temp != NULL)
	{
		free_doublptr(temp->args);
		if (temp->input != NULL)
			free_rdr(&temp->input);
		if (temp->output != NULL)
			free_rdr(&temp->output);
		del_node = temp;
		temp = temp->next;
		free(del_node);
	}
	free(temp);
	*head = NULL;
}
