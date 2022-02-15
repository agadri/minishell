/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconcy <sconcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:26:20 by adegadri          #+#    #+#             */
/*   Updated: 2022/01/31 14:39:23 by sconcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tabi2(t_env *env)
{
	int	i;

	i = 0;
	while (env->tab[i])
	{
		free(env->tab[i]->args);
		free(env->tab[i]->val);
		free(env->tab[i]);
		i++;
	}
	if (env->tab)
	{
		env->tab = NULL;
		free(env->tab);
	}
}

t_tab	**copy_in_tab_unset(t_tab **tab, t_env *env, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env->tab[i])
	{
		tab[j] = malloc(sizeof(t_tab) * 1);
		if (!tab[j])
			return (0);
		if (ft_strcmp(env->tab[i]->args, var))
		{
			tab[j]->args = ft_strdup(env->tab[i]->args);
			tab[j]->val = ft_strdup(env->tab[i]->val);
			j++;
		}
		i++;
	}
	return (tab);
}

int	built_in_unset(t_env *env, char *var)
{
	int		i;
	int		j;
	t_tab	**tab;

	env->tab_size -= 1;
	tab = malloc(sizeof(t_tab *) * (env->tab_size + 1));
	if (!tab)
		return (0);
	tab = copy_in_tab_unset(tab, env, var);
	env->tab = malloc(sizeof(char *) * (env->tab_size + 1));
	if (!env->tab)
		return (0);
	env->tab[env->tab_size] = NULL;
	i = -1;
	j = 0;
	while (++i < env->tab_size)
	{
		env->tab[j] = malloc(sizeof(t_tab) * 1);
		if (!env->tab[j])
			return (0);
		env->tab[j]->args = ft_strdup(tab[i]->args);
		env->tab[j]->val = ft_strdup(tab[i]->val);
		j++;
	}
	return (1);
}
