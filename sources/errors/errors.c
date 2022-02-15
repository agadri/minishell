/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:25:06 by sconcy            #+#    #+#             */
/*   Updated: 2022/02/08 17:26:05 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quote(char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			flag = find_next_quote(str, &i);
		}
		else if (str[i] == '\"')
		{
			i++;
			flag = find_next_dquote(str, &i);
		}
		else
			i++;
	}
	return (flag);
}

int	find_next_quote(char *str, int *i)
{
	*i += 1;
	while (str[*i])
	{
		if (str[*i] == '\'')
			return (1);
		*i += 1;
	}
	return (0);
}

int	find_next_dquote(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '\"')
		{
			*i += 1;
			return (0);
		}
		*i += 1;
	}
	return (1);
}

int	check_redirection_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
		}
		if (str[i] == '<')
		{
			if (!put_err1(str, i))
				return (0);
		}
		else if (str[i] == '>')
		{
			if (!put_err2(str, i))
				return (0);
		}
	}
	return (1);
}

int	check_parse_error(char *str)
{
	int	i;

	i = 0;
	if (check_quote(str))
	{
		write (1, "unclosed dquote or quote", 24);
		return (0);
	}
	i = check_quote_and_skip(str, i);
	if (!check_redirection_error(str))
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
		{
			while (str[i] == ' ')
				i++;
			if (str[i] == '|')
				return (0);
		}
		i++;
	}
	return (1);
}
