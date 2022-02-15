/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconcy <sconcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:36:55 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/15 14:38:08 by sconcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_atoi(char *str)
{
	int	neg;
	int	i;
	int	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v' \
	|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

char	*ft_argsdup(char *str)
{
	char	*dup;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (!str)
		return (NULL);
	while (str[len] && str[len] != '=')
		len++;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (str[i] && str[i] != '=')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*copyval(char *dup, char *str, int j)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[j])
	{
		dup[i] = str[j];
		i++;
		j++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_valdup(char *str)
{
	char	*dup;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = 0;
	while (str[len] && str[len] != '=')
	{	
		len++;
		j++;
	}
	len++;
	j++;
	while (str[len])
	{
		len++;
		i++;
	}
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (dup == NULL)
		return (NULL);
	dup = copyval(dup, str, j);
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	dest = malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
