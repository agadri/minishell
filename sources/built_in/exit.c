/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:56:28 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/15 15:55:03 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	is_charspe(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '<' && str[i + 1] == '<') || \
		(str[i] == '>' && str[i + 1] == '>'))
		{
			if (str[i] == '<')
				printf("%s\n", "bash: syntax error near unexpected token '<<'");
			else
				printf("%s\n", "bash: syntax error near unexpected token '>>'");
			return (1);
		}
		else if ((str[i] == '<' && str[i + 1] != '<') || \
		(str[i] == '>' && str[i + 1] != '>'))
		{
			if (str[i] == '<')
				printf("%s\n", "bash: syntax error near unexpected token '<'");
			else
				printf("%s\n", "bash: syntax error near unexpected token '>'");
			return (2);
		}
	}
	return (0);
}

int	is_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/' && str[i + 1] != '/')
		{
			printf("%s\n", "bash: syntax error near unexpected token '<'");
			return (1);
		}
		else if (str[i] == '>' && str[i + 1] != '>')
		{
			printf("%s\n", "bash: syntax error near unexpected token '>'");
			return (1);
		}
		i++;
	}
	return (0);
}

void	built_in_exit(t_lexer *lexer, t_free *struct_free, \
int (*fd)[2048][2], t_env *envi)
{	
	if (exit_status(lexer) == 1)
	{
		close_fds(fd, lexer->n_command);
		free_lexer(lexer);
		free(struct_free->buff);
		free(struct_free->id_fork);
		free(struct_free->str);
		free_env(envi);
		exit (g_exit);
	}
}

int	exit_status(t_lexer *lexer)
{
	if (lexer->command[0].n_token > 1
		&& !is_str_num(lexer->command[0].token[1].data))
	{
		g_exit = 2;
		ft_putstr_error("SoloMinishell: exit: ");
		ft_putstr_error(lexer->command[0].token[1].data);
		ft_putstr_error(": numeric argument required\n");
		return (0);
	}
	else if (lexer->command[0].n_token > 2)
	{
		ft_putstr_error("SoloMinishell: exit: too many arguments\n");
		g_exit = 1;
		return (0);
	}
	else if (lexer->command[0].n_token == 2)
	{
		g_exit = ft_atoi(lexer->command[0].token[1].data);
		if (g_exit < 0)
			g_exit = (g_exit % -256) + 256;
		else
			g_exit = g_exit % 256;
	}
	return (1);
}
