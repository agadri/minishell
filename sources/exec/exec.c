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

void	exec_command(t_lexer *lexer, char **env)
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
	printf("1\n");
	while (i < lexer->n_command)
	{
		printf("2\n");
		//printf("return %d\n", is_built_in(lexer->command[i].token[0].data));
		if (is_built_in(lexer->command[i].token[0].data) == 1)
		{
			printf("ICI\n");
			printf("3\n");
			//printf("token 0%s\n", lexer->command[i].token[0].data);//echo
			if (!ft_strcmp(lexer->command[i].token[0].data, "echo"))
			{
				//si il y a -n en position 1 et quelque chose en 2 printf de se au'il y a en [2]
				if(!ft_strcmp(lexer->command[i].token[1].data, "-n"))
					printf("cas 1 %s", lexer->command[i].token[2].data);
				else if (lexer->command[i].token[1].data)// sinon print avec '\n'
					printf("cas 2 %s\n", lexer->command[i].token[1].data);
			}
			if (!ft_strcmp(lexer->command[i].token[0].data, "env"))
			{
				built_in_env(lexer);//loraue t'affiche env 3 fois env segfault
			}
			if (!ft_strcmp(lexer->command[i].token[0].data, "pwd"))
			{
				built_in_pwd();//meme chose
			}
			if (!ft_strcmp(lexer->command[i].token[0].data, "export") && lexer->command[i].token[1].data)
			{
				built_in_export(lexer, lexer->command[i].token[1].data);
			}
			if (!ft_strcmp(lexer->command[i].token[0].data, "unset") && lexer->command[i].token[1].data)
			{
				built_in_unset(lexer, lexer->command[i].token[1].data);
			}
			/////////////////////////////////////////////////////
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

