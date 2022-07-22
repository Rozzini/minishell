/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:46:21 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/22 20:55:34 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//helper function for Chek_q()
//changes value of quote flag to oposite
int	check_q_change_val(int q)
{
	if (q == 1)
		return (0);
	else
		return (1);
}

// " = 34   ' = 39
//returns 1 if string have opened quote
int	check_q(char *s)
{
	int	i;
	int	sq;
	int dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 39)
			sq = check_q_change_val(sq);
		if (s[i] == 34)
			dq = check_q_change_val(dq);
		i++;
	}
	if (sq == 1 || dq == 1)
		return (1);
	return (0);
}
