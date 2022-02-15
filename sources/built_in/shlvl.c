/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconcy <sconcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:09:04 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/15 12:44:32 by sconcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len(long nb)
{
	int	len;

	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char	*str;
	long	n;
	int		i;

	n = nb;
	i = len(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}

int	get_shlvl(t_env *envi)
{
	int	i;

	i = 0;
	while (i < envi->tab_size)
	{
		if (!ft_strcmp(envi->tab[i]->args, "SHLVL"))
			return (ft_atoi(envi->tab[i]->val));
		i++;
	}
	return (1);
}

void	set_lvl(char **env, t_env *envi)
{
	int		i;
	char	*temp;
	char	*temp2;
	
	temp2 = ft_itoa(get_shlvl(envi));
	temp = ft_join("SHLVL=", temp2);
	free (temp2);
	temp2 = NULL;
	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(env[i], temp))
		{
			free(temp);
			temp2 = ft_itoa(get_shlvl(envi) + 1);
			temp = ft_join("SHLVL=", temp2);
			env[i] = ft_strdup(temp);
			free (temp2);
			free (temp);
			break ;
		}
		i++;
	}
}
