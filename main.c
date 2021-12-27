#include "includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_lexer *lexer;
	char **str;
	char *buff;
	

	// char *test;
	printf("env --> %s\n" ,env[0]);
	while (1)
	{
		// buff = add_space_between_redir(readline("Solo_Minishell> "));
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
	//	 if (!check_parse_error(buff))
	//	 {
	//	 	free (buff);
	//	 	return (0);
	//	 }
			buff = add_space_between_redir(buff);
			add_history(buff);
			str = ft_split(buff, '|');
			lexer = init_lexer(str);
			take_and_cpy_env(env, lexer);
			// print_lexer_struct(lexer);
			exec_command(lexer, env);
			free(buff);
			free_double_array(str);
			free_lexer(lexer);
		}
	}
	return (0);
}
