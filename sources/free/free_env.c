/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:08:59 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/15 16:24:20 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_arg1(t_env *env)
{
	if (env->tab)
	{
		free (env->tab);
		env->tab = NULL;
	}
	if (env->pwd != NULL)
	{
		free(env->pwd);
		env->pwd = NULL;
	}
	if (env->oldpwd)
	{
		free(env->oldpwd);
		env->oldpwd = NULL;
	}
	if (env->home)
	{
		free(env->home);
		env->home = NULL;
	}
}

void	ft_free_arg2(t_env *env)
{
	if (env->shlvl)
	{
		free(env->shlvl);
		env->shlvl = NULL;
	}
	if (env->path)
		env->path = NULL;
	if (env)
		free (env);
}

void	free_env(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->tab_size)
	{
		if (env->tab[i]->args)
		{
			free (env->tab[i]->args);
			env->tab[i]->args = NULL;
		}
		if (env->tab[i]->val)
		{
			free (env->tab[i]->val);
			env->tab[i]->val = NULL;
		}
		if (env->tab[i])
		{
			free (env->tab[i]);
			env->tab[i] = NULL;
		}
	}
	ft_free_arg1(env);
	ft_free_arg2(env);
}
