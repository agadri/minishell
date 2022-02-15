/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:31:42 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/15 15:56:01 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_built_in(char *cmd)
{
	static char	*tab[] = \
	{"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};//bin/echo blablabla
	int			i;

	i = 0;
	if (!cmd)
		return (2);
	while (tab[i])
	{
		if (!ft_strcmp(tab[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

void	exec_built_in(int i, t_env *envi, t_lexer *lexer)
{
	if (!ft_strcmp(lexer->command[i].token[0].data, "echo"))
		built_in_echo(i, lexer);
	else if (!ft_strcmp(lexer->command[i].token[0].data, "env"))
		built_in_env(envi);
	else if (!ft_strcmp(lexer->command[i].token[0].data, "pwd"))
		printf_pwd(envi);
}

int	check_if_in_env(t_env *env, char *var)
{
	int		i;
	char	*vardup;

	i = 0;
	vardup = ft_argsdup(var);
	while (i < env->tab_size)
	{
		if (!ft_strcmp(vardup, env->tab[i]->args))
		{
			free (vardup);
			return (1);
		}
		i++;
	}
	free (vardup);
	return (0);
}

void	change_val(t_env *env, char *var)
{
	int		i;
	char	*vardup;

	i = 0;
	vardup = ft_argsdup(var);
	while (i < env->tab_size)
	{
		if (!ft_strcmp(vardup, env->tab[i]->args))
		{
			free(env->tab[i]->val);
			env->tab[i]->val = ft_valdup(var);
			free (vardup);
		}
		i++;
	}
}
