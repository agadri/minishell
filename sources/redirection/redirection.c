#include "../../includes/minishell.h"

void	ft_putstr_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	make_redirection(t_command *command, int (*fd)[2048][2], int fd_index)
{
	int i = 0;

	while (i < command->n_token)
	{
		if (command->token[i].type == FILE_OUT)
		{
			(*fd)[fd_index][1] = open(command->token[i + 1].data, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if ((*fd)[fd_index][1] < 0)
				return ;
		}
		else if(command->token[i].type == FILE_OUT_SUR)
		{
			(*fd)[fd_index][1] = open(command->token[i + 1].data, O_RDWR | O_CREAT | O_APPEND, 0644);
			if ((*fd)[fd_index][1] < 0)
				return ;
		}
		else if (command->token[i].type == FILE_IN)
		{
			(*fd)[fd_index][0] = open(command->token[i + 1].data, O_RDONLY);
			if ((*fd)[fd_index + 1][0] < 0)
				return ;
		}
		i++;
	}
}

void	treat_redirection(t_command *command, int (*fd)[2048][2], int fd_index, int n_command)
{
	int i = 0;
 	int ret_1;
	int ret_2;
	
	ret_1 = 0;
	ret_2 = 0;

	while (i < command->n_token)
	{
		if (command->token[i].type == FILE_OUT || command->token[i].type == FILE_OUT_SUR)
		{
			ret_1 = 1;
			dup2((*fd)[fd_index][1], STDOUT_FILENO);
		}
		else if (command->token[i].type == FILE_IN || command->token[i].type == HERE_DOC)
		{
			ret_2 = 1;
			dup2((*fd)[fd_index][0], STDIN_FILENO);
		}
		i++;
	}
	if (fd_index + 1 < n_command && !ret_1)
		dup2((*fd)[fd_index][1], STDOUT_FILENO);
	if (fd_index > 0 && !ret_2)
		dup2((*fd)[fd_index][0], STDIN_FILENO);
}

// void	here_doc(char *eof, int (*fd)[2048][2], int i)
// {
// 	char    *buff;
//     int        len;

//     buff = readline("> ");
//     while (ft_strcmp(buff, eof) != 0)
//     {
// 		len = ft_strlen(buff);
//         write((*fd)[i][1], buff, len - 1);
//         free(buff);
//         buff = readline("> ");
//     }
//     free(buff);
// }

// int	treat_here_doc()
// {
	
// }