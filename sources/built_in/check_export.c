/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:26:07 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/07 19:39:37 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_name_var(char *str)
{
	if (!str || !str[0])
		return (0);
	if (str[0] != '_' && (!(str[0] >= 'a' && str[0] <= 'z') && \
	!(str[0] >= 'A' && str[0] <= 'Z')))
		return (1);
	return (0);
}

int	check_if_equal(char *str)
{
	int	i;
	int	stat;

	i = 1;
	stat = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			stat += 1;
		i++;
	}
	if (stat == 1)
		return (1);
	return (0);
}

void	add_to_export(t_env *env, char *var)
{
	env->exp_tab[env->exp_tab_size] = ft_strdup(var);
	env->exp_tab_size += 1;
}
