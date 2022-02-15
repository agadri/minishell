/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:40:42 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/08 14:42:16 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*init_lexer(char **str, t_env *envi)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->command = init_command_struct(str, lexer, envi);
	return (lexer);
}

int	init_tab(t_env **envi)
{
	*envi = malloc(sizeof(t_env));
	if (!*envi)
		return (0);
	(*envi)->tab = NULL;
	(*envi)->pwd = NULL;
	(*envi)->shlvl = NULL;
	(*envi)->oldpwd = NULL;
	(*envi)->home = NULL;
	(*envi)->path = NULL;
	(*envi)->tab_size = 0;
	(*envi)->exp_tab_size = 0;
	(*envi)->state = 0;
	return (1);
}
