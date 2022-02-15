/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:23:11 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/15 16:21:10 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int g_exit = 0;

#include "includes/minishell.h"

void	handler_sigint(int signum)
{
	if (signum == SIGINT)
	{
		g_exit = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		return ;
}

void	print_lexer_struct(t_lexer *lexer)
{
	int i;
	int j;

	i = 0;
	printf("NUMBER OF COMMAND	:		%d\n\n\n", lexer->n_command);
	while (i < lexer->n_command)
	{
		j = 0;
		printf("COMMAND			:		%s\n", lexer->command[i].command);
		printf("NUMBER OF TOKEN		:		%d\n\n", lexer->command[i].n_token);
		while (j < lexer->command[i].n_token)
		{
			printf("TOKEN			:		%s\n", lexer->command[i].token[j].data);
			printf("TYPE			:		%d\n\n", lexer->command[i].token[j].type);
			j++;
		}
		printf("\n\n\n\n");
		i++;
	}
}

int	if_main_else(t_env *envi, t_lexer *lexer, char **env, t_free struct_free)
{
	struct_free.buff = add_space_between_redir(struct_free.buff);
	add_history(struct_free.buff);
	struct_free.str = ft_split(struct_free.buff, '|');
	take_and_cpy_env(envi, env);
	envi->state = 1;
	lexer = init_lexer(struct_free.str, envi);
	if (!lexer)
	{
		free_env(envi);
		return (0);
	}
	exec_command(envi, lexer, env, &struct_free);
	free(struct_free.buff);
	free_double_array(struct_free.str);
	free_lexer(lexer);
	//free_env(envi);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	static t_lexer	*lexer = NULL;
	t_free			struct_free;
	t_env			*envi;

	(void)argc;
	(void)argv;
	(void)env;
	if (!init_tab(&envi))
		return (0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	struct_free.buff = NULL;
	struct_free.str = NULL;
	while (1)
	{
		signal(SIGINT, handler_sigint);
		struct_free.buff = readline("Solo_Minishell> ");
		if (!struct_free.buff)
		{
			write(1, "exit\n", 5);
			free_env(envi);
			exit(g_exit);
		}
		if (!*struct_free.buff)
			free(struct_free.buff);
		else
		{
			if (!if_main_else(envi, lexer, env, struct_free))
				return (0);
		}
	}
	free_env(envi);
	return (0);
}
