#include "includes/minishell.h"


int	init_tab(t_env **envi)
{
	*envi = malloc(sizeof(t_env));
	if (!*envi)
		return (0);
	(*envi)->tab = NULL;
	(*envi)->pwd = NULL;
	(*envi)->oldpwd = NULL;
	(*envi)->home = NULL;
	(*envi)->tab_size = 0;
	return (1);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	static t_lexer *lexer = NULL;
	t_env *envi = NULL;
	char **str;
	char *buff;

	if (!init_tab(&envi))
		return (0);
	signal(SIGINT, ctrl_c_handler);
	signal(SIGTSTP, ctrl_z_handler);
	signal(SIGQUIT, ctrl_s_handler);
	while (1)
	{
		buff = readline("Solo_Minishell> ");
		if (!buff)
		{
			write(1, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}

		if (!*buff)
			free(buff);
		else
		{
			buff = add_space_between_redir(buff);
			add_history(buff);
			str = ft_split(buff, '|');
			if (init_lexer(&lexer, str) == NULL)
				return (1);
			take_and_cpy_env(envi, env, lexer);
			lexer->state_of_init = 1;
			printf("1STAT %d\n",lexer->state_of_init);
			exec_command(envi, lexer, env);
			free(buff);
			free_double_array(str);
			free_lexer(lexer);
		}
	}
	return (0);
}
