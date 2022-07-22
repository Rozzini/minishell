/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:01:04 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/22 21:05:34 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	push(t_env **head_ref, char *key, char *val)
{
	t_env	*new_node;

	new_node = (t_env *) malloc(sizeof(t_env));
	new_node->key = key;
	new_node->val = val;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

void	delete_node(t_env **head)
{
	t_env	*temp;

	temp = *head;
	*head = (*head)->next;
    free(temp->key);
    free(temp->val);
	free(temp);
}