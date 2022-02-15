/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_all_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconcy <sconcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:28:40 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/15 13:53:26 by sconcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	rmove_quote1(char *str, int i, int count)
{
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				i++;
				count++;
			}
			if (str[i] == '\'')
				i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (i < ft_strlen(str) && str[i] != '\"')
			{
				i++;
				count++;
			}
			if (str[i] == '\"')
				i++;
		}
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

char	*rmove_quote2(char *str, int i, int count, char *dest)
{
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
			{
				dest[count] = str[i];
				i++;
				count++;
			}
			if (str[i] == '\'')
				i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				dest[count] = str[i];
				i++;
				count++;
			}
			if (str[i] == '\"')
				i++;
		}
		else
		{
			dest[count] = str[i];
			i++;
			count++;
		}
	}
	dest[count] = '\0';
	free(str);
	return (dest);
}
