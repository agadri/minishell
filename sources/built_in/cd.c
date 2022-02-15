/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saul <saul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:13:30 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/03 19:55:24 by saul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	if_home(t_env *env, char *path)
{
	if (chdir(env->home) == -1)
		perror (path);
}

void	if_path(t_env *env, char *path)
{
	char	*chem;

	chem = ft_strjoin(env->path, path);
	if (chdir(chem) == -1)
	{
		free(chem);
		if (chdir(path) == -1)
			perror(path);
		perror(chem);
	}
	free(chem);
}

void	built_in_cd(t_env *env, char *path)
{
	if (env->oldpwd)
		free(env->oldpwd);
	env->oldpwd = ft_strdup(built_in_pwd(env));
	if (!path && env->home)
		if_home(env, path);
	else if (path && !ft_strcmp(path, "-"))
	{
		printf("-\n");
		chdir(env->oldpwd);
	}
	else if (path && env->path)
		if_path(env, path);
	else
	{
		if (chdir(path) == -1)
			perror(path);
	}
}
