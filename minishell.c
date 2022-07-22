/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:25:11 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/22 20:46:27 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(int argc, char **argv, char **env)
{
	if (argc == 1)
		return (0);
	if (check_q(argv[1]) == 1)
		return (0);
	printf("input: %s\n", argv[1]);
	find_env(argv[1]);
	//const char* s = getenv("PATH");
	//printf("PATH :%s\n",(s!=NULL)? s : "getenv returned NULL");
    return (0);
}
