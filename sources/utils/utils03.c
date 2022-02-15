/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils03.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:17:59 by sconcy            #+#    #+#             */
/*   Updated: 2022/02/08 17:19:49 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_new_limitor(char *limitor, int count)
{
	int		i;

	i = 0;
	count = 0;
	while (limitor[i])
	{
		if (limitor[i] == '\'' || limitor[i] == '\"')
			i++;
		else
			count++;
		i++;
	}
	return (count);
}

char	*remove_quote_from_limitor(char *limitor)
{
	int		i;
	int		count;
	char	*new_limitor;

	count = 0;
	count = size_new_limitor(limitor, count);
	new_limitor = (char *)malloc(sizeof(char) * (count + 1));
	if (!new_limitor)
		return (NULL);
	i = 0;
	count = 0;
	while (limitor[i])
	{
		if (limitor[i] == '\'' || limitor[i] == '\"')
			i++;
		else
		{
			new_limitor[count] = limitor[i];
			count++;
		}
		i++;
	}
	new_limitor[count] = '\0';
	return (new_limitor);
}

int	has_quote(char *limitor)
{
	int	i;

	i = 0;
	while (limitor[i])
	{
		if (limitor[i] == '\'' || limitor[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	has_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
