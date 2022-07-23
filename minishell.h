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
	int			arg_c;
	int			pipe_c;
}				t_tokens;

typedef struct	s_env
{
	char		*key;
	char		*val;
	struct	s_env	*next;
}				t_env;


//====================BUILTINS=====================//

//for now returns 0 if successfully executed
//returns 1 if not executed
int		ft_echo(t_tokens *tokens);

int		ft_pwd(t_tokens *tokens);

int		ft_cd(t_tokens *tokens);

int		ft_env(t_tokens *tokens, t_env **env_list);

//=================================================//



//====================EXECUTION=====================//

//launches execution routine
void    try_execute(t_tokens *tokens, t_env **env);

//tries to execute builtins
//if one of them executed successfully returns 0;
//else returns 1;
int     try_builtins(t_tokens *tokens, t_env **env);

//==================================================//



//=====================PARSING======================//

//returns 1 if string have opened quote
//returns 0 if everything fine
int	    check_q(char *s);

//temp function
//just splits arguments and count them
int     basic_parsing(t_tokens *tokens);

//==================================================//



//====================ALL_LIST======================//

//adds new node to list of env
//returns 1 if quote is not closed
void	push(t_env **head_ref, char *key, char *val);

//removes node from list env
void	delete_node(t_env **head);

//duplicates env variables into list t_env
void    init_env_list(t_env **env_list, char **env);

//prints duplicated env variables
void	print_env(t_env **head);

//==================================================//


#endif