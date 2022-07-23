#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

typedef struct	s_tokens
{
	char		*cmdl;
    char		**args;
	int			pipe_c;
}				t_tokens;

typedef struct	s_env
{
	char		*key;
	char		*val;
	struct	s_env	*next;
}				t_env;

//====================BUILTINS=====================//

void	ft_echo(char **av);

void	ft_pwd(int ac, char **av);

void	ft_cd(int ac, char **av);

void    ft_env(t_env **env_list);

//=================================================//


//returns 1 if string have opened quote
int	    check_q(char *s);

//adds new node to list of env
void	push(t_env **head_ref, char *key, char *val);

//removes node from list env
void	delete_node(t_env **head);

//duplicates env variables into list t_env
void    init_env_list(t_env **env_list, char **env);

//prints duplicated env variables
void	print_env(t_env **head);


//---------SECTION FOR TEMP FUNCTIONS---------------//

int     basic_parsing(t_tokens *tokens);

#endif