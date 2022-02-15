/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconcy <sconcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:42:38 by adegadri          #+#    #+#             */
/*   Updated: 2022/02/15 15:22:28 by sconcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    echo_n(int i, t_lexer *lexer)
{
    int    j;

    j = check_n_echo(lexer, i) + 1;
    while (j < lexer->command[i].n_token)
    {
        printf("%s", lexer->command[i].token[j].data);
		if (j < lexer->command[i].n_token - 1)
        	printf("%c", ' ');
        j++;
    }
}

void    echo_(int i, t_lexer *lexer)
{
    int    j;

    j = 1;
    while (j < lexer->command[i].n_token)
    {
        printf("%s", lexer->command[i].token[j].data);
		if (j < lexer->command[i].n_token - 1)
        	printf("%c", ' ');
        j++;
    }
    printf("\n");
}

void    built_in_echo(int i, t_lexer *lexer)
{
    if (lexer->command[i].n_token > 1)
    {
        if (check_n_echo(lexer, i))
            echo_n(i, lexer);
        else
            echo_(i, lexer);
    }
}

int    is_only_n(char *str)
{
    int i;
    int len;
    int count;
    
    count = 1;
    len = ft_strlen(str);
    i = 1;
    if (str[0] == '-')
    {
        while (str[i])
        {
            if (str[i] == 'n')
                count++;
            i++;
        }
    }
    if (count == len)
        return (1);
    else
        return (0);
}

int    check_n_echo(t_lexer *lexer, int i)
{
    int j;
    int flag;

    j = 1;
    flag = 0;
    while (j < lexer->command[i].n_token)
    {
        if (is_only_n(lexer->command[i].token[j].data))
            flag += 1;
        j++;
    }
    return (flag);
}
