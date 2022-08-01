/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:46:21 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/29 21:35:44 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//printf("AAA\n");
//helper function for Chek_q()
//changes value of quote flag to oposite
int	check_q_change_val(int q)
{
	if (q == 1)
		return (0);
	else
		return (1);
}

char	*check_q_iter(char *s, int *q, char quote)
{
	if (*s == quote)
	{
		*q = check_q_change_val(*q);
		s++;
		while (*s != quote && *s != '\0')
		{
			s++;
			if (*s == quote)
				*q = check_q_change_val(*q);
		}
	}
	return (s);
}

// " = 34   ' = 39
//returns 1 if string have opened quote
int	check_q(char *s)
{
	int	q;

	q = 0;
	while (*s != '\0')
	{
		if (*s == 34 || *s == 39)
			s = check_q_iter(s, &q, *s);
		if (*s == '\0')
			break ;
		s++;
	}
	if (q == 1)
		return (1);
	return (0);
}
