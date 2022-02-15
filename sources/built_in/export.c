/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 18:00:13 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/15 16:11:10 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tabi(t_env *env)
{
	int	i;

	i = 0;
	while (env->tab[i])
	{
		free(env->tab[i]);
		env->tab[i] = NULL;
		i++;
	}
	free(env->tab);
	env->tab = NULL;
	
}

int	check_var(char *var)
{
	char	*check;

	check = ft_valdup(var);
	if (!check[0])
		return (1);
	free (check);
	return (0);
}

t_tab	**copy_in_tab_export(t_tab **tab, t_env *env, char *var)
{
	int	i;

	i = -1;
	while (env->tab[++i])
	{
		tab[i] = malloc(sizeof(t_tab) * 1);
		if (!tab[i])
			return (NULL);
		tab[i]->args = ft_strdup(env->tab[i]->args);
		tab[i]->val = ft_strdup(env->tab[i]->val);
		//i++;
	}
	tab[i] = malloc(sizeof(t_tab) * 1);
	tab[i + 1] = malloc(sizeof(t_tab) * 1);
	if (!tab[i] || !tab[i + 1])
		return (NULL);
	tab[i]->args = ft_argsdup(var);
	tab[i]->val = ft_valdup (var);
	tab[i + 1]->args = NULL;
	tab[i + 1]->val = NULL;
	return (tab);
}

void	built_in_export(t_env *env, char *var)
{
	int		i;
	t_tab	**tab;

	env->tab_size += 1;
	tab = malloc(sizeof(t_tab *) * (env->tab_size + 1));
	if (!tab)
		return ;
	tab = copy_in_tab_export(tab, env, var);
	free_tabi(env);
	env->tab = malloc(sizeof(t_tab *) * (env->tab_size + 1));
	if (!env->tab)
		return ;
	env->tab[env->tab_size] = NULL;
	i = -1;
	while (++i < env->tab_size)
	{
		env->tab[i] = malloc(sizeof(t_tab) * 1);
		if (!env->tab[i])
			return ;
		env->tab[i]->args = ft_strdup(tab[i]->args);
		env->tab[i]->val = ft_strdup(tab[i]->val);
	}
}

void	export_error(t_lexer *lexer, int index)
{
	int	i;

	i = 2;
	while (i < lexer->command[index].n_token)
	{
		printf("Solo_Minishell: export: `%s': not a valid identifier\n",
			lexer->command[index].token[i].data);
		i++;
	}
}
