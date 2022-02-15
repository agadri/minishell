/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:23:03 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/08 17:20:49 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	put_err1(char *str, int i)
{
	if (!str[i + 1])
	{
		printf("bash: syntax error near unexpected token `newline'");
		return (0);
	}
	if (str[i + 1] && str[i + 1] == '>')
	{	
		write(1, "bash : syntax error near unexpected token '>'", 45);
		return (0);
	}
	else if (str[i - 1] == '<' && str[i + 1] && str[i + 1] == '<')
	{
		write(1, "bash : syntax error near unexpected token '", 43);
		write(1, &str[i], 1);
		write(1, "'", 1);
		return (0);
	}
	return (1);
}

int	put_err2(char *str, int i)
{
	if (!str[i + 1])
	{
		printf("bash: syntax error near unexpected token `newline'");
		return (0);
	}
	if (str[i + 1] && str[i + 1] == '<')
	{
		write(1, "bash : syntax error near unexpected token '<'", 45);
		return (0);
	}
	else if (str[i - 1] == '>' && (str[i + 1] && str[i + 1] == '>'))
	{
		write(1, "bash : syntax error near unexpected token '", 43);
		write(1, &str[i], 1);
		write(1, "'", 1);
		return (0);
	}
	return (1);
}

int	check_quote_and_skip(char *str, int i)
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
	return (i);
}
