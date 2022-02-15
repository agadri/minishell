/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconcy <sconcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:30:02 by sconcy            #+#    #+#             */
/*   Updated: 2022/02/06 15:33:02 by sconcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(t_token *token)
{
	if (token->data)
		free (token->data);
}

void	free_command(t_command *command)
{
	int	i;

	i = 0;
	while (command && i < command->n_token)
	{
		if (&command->token[i])
			free_token(&command->token[i]);
		i++;
	}
	if (command && command->command)
		free (command->command);
	if (command && command->token)
		free (command->token);
	if (command && command->args)
		free_double_array(command->args);
}

void	free_lexer(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (i < lexer->n_command)
	{
		free_command(&lexer->command[i]);
		i++;
	}
	free (lexer->command);
	free (lexer);
}
