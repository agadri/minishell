/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:36:06 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/08 17:34:44 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sizetab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

char	*check_env(t_env *envi, char *str)
{
	int	i;

	i = 0;
	while (i < envi->tab_size)
	{
		if (ft_strcmp(str, envi->tab[i]->args) == 0)
			return (envi->tab[i]->val);
		i++;
	}
	return (NULL);
}
