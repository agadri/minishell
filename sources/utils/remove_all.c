/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconcy <sconcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:52:55 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/15 14:38:52 by sconcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_all_dollar_from_command(t_command *command, t_env *envi)
{
	int		i;
	int		j;
	// char	*temp;

	(void)envi;
	j = 0;
	i = 0;
	while (i < command->n_token)
	{
		j = 0;
		if (command->token[i].type == ARG)
		{
			while (is_dollar(command->token[i].data))
				command->token[i].data
					= treat_dollar(command->token[i].data, envi);
			while (j < ft_strlen(command->token[i].data) && command->token[i].data[j])
			{
				if (command->token[i].data[j] == '$')
				{
					command->token[i].data = remove_dollar(command->token[i].data, j, envi);
				}
				if (command->token[i].data[j] == '\'')
				{
					j++;
					while (command->token[i].data[j] && command->token[i].data[j] != '\'')
						j++;
					if (command->token[i].data[j] == '\'')
						j++;
				}
				else if (command->token[i].data[j] == '\"')
				{
					j++;
					while (command->token[i].data[j] && command->token[i].data[j] != '\"')
					{
						if (command->token[i].data[j] == '$')
						{
							command->token[i].data = remove_dollar(command->token[i].data, j, envi);
						}
						j++;
					}
					if (command->token[i].data[j] == '\"')
						j++;
				}
				j++;
			}
		}
		i++;
	}
}

char	*remove_all_quote(char *str)
{
	int		i;
	int		count;
	char	*dest;

	i = 0;
	count = 0;
	count = rmove_quote1(str, i, count);
	dest = (char *)malloc(sizeof(char) * (count + 1));
	if (!dest)
		return (NULL);
	i = 0;
	count = 0;
	dest = rmove_quote2(str, i, count, dest);
	return (dest);
}

void	remove_all_quote_from_command(t_command *command)
{
	int	i;

	i = 0;
	while (i < command->n_token)
	{
		command->token[i].data = remove_all_quote(command->token[i].data);
		i++;
	}
}

char	*remove_dollar_from_string(char *string)
{
	char	*new_string;
	int		i;
	int		j;

	i = 1;
	j = 0;
	new_string = (char *)malloc(sizeof(char) * (ft_strlen(string)));
	if (!new_string)
		return (NULL);
	while (string[i])
	{
		new_string[j] = string[i];
		i++;
		j++;
	}
	new_string[j] = '\0';
	return (new_string);
}