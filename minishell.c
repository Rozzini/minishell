/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:25:11 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/22 18:29:16 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_token
{
	char            *cmdl;
    	char            **args;
	char		*path;
	char		*file_red;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct	s_env
{
	char		*key;
	char		*val;
	struct	s_env	*next;
}				t_env;

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

void	process_env(char *s)
{
	int	i;
	int	l;
	char	*env;

	i = 0;
	while(s[i] != '\0' || s[i] != ' ' || s[i] != '\t')
	{
		l++;
		i++;
	}
	env = (char *)malloc(sizeof(char) * (l + 1));
	i = 0;
	while (i < l)
	{
		env[i] = s[i];
		i++;
	}	
	env[i] = '\0';
	printf("env: %s\n",env);
}

void	find_env(char *s)
{
	char *c;

	c = strchr(s, '$');
	if (c == NULL)
	{
		printf("there is no ENV var\n");
		return ;	
	}
	process_env(c);
}

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
