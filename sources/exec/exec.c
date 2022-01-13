#include "../../includes/minishell.h"

void	wait_all_pid(int *id_fork, int n_fork)
{
	int i = 0;

	while (i < n_fork)
	{
		if (waitpid(id_fork[i], 0, 0) == -1)
		i++;
	}
}

char	*find_bin(t_command *command)
{
	char	**pathes;
	char	*tmp_path;
	char	*com;
	int 	i;

	i = 0;
	tmp_path = getenv("PATH");
	pathes = ft_split(tmp_path, ':');
	com = ft_join("/", command->token[0].data);
	while (pathes[i])
	{
		tmp_path = ft_join(pathes[i], com);
		if (access(tmp_path, F_OK) == 0)
		{
			free_double_array(pathes);
			free (com);
			return (tmp_path);
		}
		free (tmp_path);
		i++;
	}
	free (com);
	free_double_array(pathes);
	return (command->token[0].data);
}

void	close_fds(int (*fd)[2048][2], int n_command)
{
	int	i;

	i = 0;
	while (i < n_command- 1)
	{
		close((*fd)[i][0]);
		close((*fd)[i][1]);
		i++;
	}
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	exec_command(t_env *envi, t_lexer *lexer, char **env)
{
 	int		i;
	int		fd[2048][2];// 0 READ |||| 1 WRITE
 	int		*id_fork;

 	i = 0;
	if (lexer->n_command > 1)
	{
		while (i < lexer->n_command - 1)
		{
			if (pipe(fd[i]) == -1)
				return ;
			i++;
		}
	}
	id_fork = (int *)malloc(sizeof(int) * lexer->n_command);
	i = 0;
	while (i < lexer->n_command)
	{
		make_redirection(&lexer->command[i], &fd, i);
		i++;
	}
	i = 0;
	while (i < lexer->n_command)
	{
		if (is_built_in(lexer->command[i].token[0].data) == 1)
		{
			if (!ft_strcmp(lexer->command[i].token[0].data, "echo"))
			{
				if(!ft_strcmp(lexer->command[i].token[1].data, "-n"))
					printf("%s", lexer->command[i].token[2].data);
				if (lexer->command[i].token[1].data[0] == '$')
				{
					int j;

					j = 0;
					while (j < envi->tab_size)
					{
						if (ft_strcmp(lexer->command[i].token[1].data, envi->tab[j]->args))
							printf("%s\n", envi->tab[j]->val);
						j++;
					}
				}
				else
					printf("%s\n", lexer->command[i].token[1].data);
					
			}
			else if (!ft_strcmp(lexer->command[i].token[0].data, "env"))
				built_in_env(envi, lexer);
			else if (!ft_strcmp(lexer->command[i].token[0].data, "cd"))
				built_in_cd(envi, lexer, lexer->command[i].token[1].data);
			else if (!ft_strcmp(lexer->command[i].token[0].data, "pwd"))
				printf_pwd(envi, lexer);
			else if (!ft_strcmp(lexer->command[i].token[0].data, "export") && lexer->command[i].token[1].data)
				built_in_export(envi, lexer, lexer->command[i].token[1].data);
			else if (!ft_strcmp(lexer->command[i].token[0].data, "unset") && lexer->command[i].token[1].data)
				built_in_unset(envi, lexer, lexer->command[i].token[1].data);
			else if (!ft_strcmp(lexer->command[i].token[0].data, "exit") && !lexer->command[i].token[1].data)
				printf("aaaahhah\n");
			else if (!ft_strcmp(lexer->command[i].token[0].data, "exit") && lexer->command[i].token[1].data)
			{
				printf("111 |%s| |%s|\n", lexer->command[i].token[0].data, lexer->command[i].token[1].data);
				built_in_exit(lexer, envi, i);
			}
		}
		else
		{
			lexer->command[i].path = find_bin(&lexer->command[i]);
			id_fork[i] = fork();
			if (id_fork[i] < 0)
				return ;
			else if (id_fork[i] == 0)
			{
				treat_redirection(&lexer->command[i], &fd, i, lexer->n_command);
				close_fds(&fd, lexer->n_command);
				execve(lexer->command[i].path, lexer->command[i].args, env);
				free_lexer(lexer);	
			}
		}
		i++;
	}
	close_fds(&fd, lexer->n_command);
	wait_all_pid(id_fork, lexer->n_command);
	free(id_fork);
}

