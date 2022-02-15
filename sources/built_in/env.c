/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconcy <sconcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:45:57 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/15 12:30:04 by sconcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cpy_first_val(t_env *envi, int i)
{
	if (!ft_strcmp(envi->tab[i]->args, "HOME"))
		envi->home = ft_strdup(envi->tab[i]->val);
	else if (!ft_strcmp(envi->tab[i]->args, "PWD"))
		envi->pwd = ft_strdup(envi->tab[i]->val);
	else if (!ft_strcmp(envi->tab[i]->args, "OLDPWD"))
		envi->oldpwd = ft_strdup(envi->tab[i]->val);
	else if (!ft_strcmp(envi->tab[i]->args, "SHLVL"))
		envi->shlvl = ft_strdup(envi->tab[i]->val);
}

int	take_and_cpy_env(t_env *envi, char **env)
{
	int	i;

	if (!env)
		return (0);
	if (envi->state == 1)
		return (0);
	envi->tab_size = sizetab(env);
	envi->tab = malloc(sizeof(t_tab *) * (envi->tab_size + 1));
	if (!envi->tab)
		return (0);
	i = -1;
	while (++i < envi->tab_size)
	{
		envi->tab[i] = malloc(sizeof(t_tab));
		if (!envi->tab[i])
			return (0);
		envi->tab[i]->args = ft_argsdup(env[i]);
		envi->tab[i]->val = ft_valdup(env[i]);
		cpy_first_val(envi, i);
	}
	envi->tab[i] = NULL;
	return (1);
}

void	built_in_env(t_env *env)
{
	int		i;

	i = -1;
	while (++i < env->tab_size)
	{
		if (!ft_strcmp(env->tab[i]->args, "PWD"))
		{
			env->pwd = built_in_pwd(env);
			printf("%s=%s\n", env->tab[i]->args, env->pwd);
		}
		else if (!ft_strcmp(env->tab[i]->args, "OLDPWD"))
			printf("%s=%s\n", env->tab[i]->args, env->oldpwd);
		else if (!ft_strcmp(env->tab[i]->args, "PWD"))
			printf("%s=%s\n", env->tab[i]->args, env->pwd);
		else if (!ft_strcmp(env->tab[i]->args, "SHLVL"))
			printf("%s=%s\n", env->tab[i]->args, env->shlvl);
		else if (!ft_strcmp(env->tab[i]->args, "CDPATH"))
		{
			env->path = ft_strdup(env->tab[i]->val);
			printf("%s=%s\n", env->tab[i]->args, env->path);
		}
		else
			printf("%s=%s\n", env->tab[i]->args,
				env->tab[i]->val);
	}
}

void	utils_built_in_env_exp(t_env *env, int i)
{
	if (!ft_strcmp(env->tab[i]->args, "PWD"))
	{
		env->pwd = built_in_pwd(env);
		printf("export %s=\"%s\"\n", env->tab[i]->args,
			env->pwd);
	}
	else if (!ft_strcmp(env->tab[i]->args, "OLDPWD"))
		printf("export %s=\"%s\"\n", env->tab[i]->args,
			env->oldpwd);
	else if (!ft_strcmp(env->tab[i]->args, "PWD"))
		printf("export %s=\"%s\"\n", env->tab[i]->args,
			env->pwd);
	else if (!ft_strcmp(env->tab[i]->args, "SHLVL"))
		printf("export %s=\"%s\"\n", env->tab[i]->args,
			env->shlvl);
	else if (!ft_strcmp(env->tab[i]->args, "CDPATH"))
	{
		env->path = ft_strdup(env->tab[i]->val);
		printf("export %s=\"%s\"\n", env->tab[i]->args,
			env->path);
	}
	else
		printf("export %s=\"%s\"\n", env->tab[i]->args,
			env->tab[i]->val);
}

void	built_in_env_exp(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->tab_size)
	{
		utils_built_in_env_exp(env, i);
		i++;
	}
	i = 0;
	while (i < env->exp_tab_size)
	{
		printf("%s\n", env->exp_tab[i]);
		i++;
	}
}
