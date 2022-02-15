/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegadri <adegadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:15:25 by sconcy            #+#    #+#             */
/*   Updated: 2022/02/15 15:52:55 by adegadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_wait_status(int status, int i, int pid, int nb_pid)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		ft_putstr_error("Quit (core dumped)\n");
		g_exit = 131;
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		ft_putstr_error("\n");
		g_exit = 130;
	}
	else if (i + 1 == nb_pid && pid != -1)
		g_exit = WEXITSTATUS(status);
}

int	wait_all_pid(int *id_fork, int n_fork)
{
	int	i;
	int	status;

	i = -1;
	while (++i < n_fork)
	{
		status = 0;
		if (id_fork[i] != -1 && waitpid(id_fork[i], &status, 0) == -1)
		{
			free(id_fork);
			return (0);
		}
		check_wait_status(status, i, id_fork[i], n_fork);
	}
	free(id_fork);
	return (0);
}

char	*find_bin(t_command *command, t_env *envi)
{
	char	**pathes;
	char	*tmp_path;
	char	*com;
	int		i;

	i = 0;
	tmp_path = check_env(envi, "PATH");
	pathes = ft_split(tmp_path, ':');
	com = ft_join("/", command->token[0].data);
	if (pathes)
	{
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
	}
	free (com);
	if (pathes)
		free_double_array(pathes);
	return (NULL);
}

void	close_fds(int (*fd)[2048][2], int n_command)
{
	int	i;

	i = 0;
	while (i <= n_command)
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

void	treat_fork(t_lexer *lexer, int (*fd)[2048][2], int i, char **env,
t_env *envi, t_free *struct_free)
{
	treat_redirection(lexer, fd, i, lexer->n_command);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (is_built_in(lexer->command[i].token[0].data) == 1)
	{	
		close_fds(fd, lexer->n_command);
		exec_built_in(i, envi, lexer);
		free(struct_free->id_fork);
		free(struct_free->buff);
		free_double_array(struct_free->str);
		free_lexer(lexer);
		free_env(envi);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close_fds(fd, lexer->n_command);
		lexer->command[i].path = find_bin(&lexer->command[i], envi);
		if (has_slash(lexer->command[i].token[0].data))
		{
			if (execve(lexer->command[i].token[0].data,
					lexer->command[i].args, env) == -1)
			{	
				ft_putstr_fd("Solo_Minishell: ", 2);
				perror(lexer->command[i].token[0].data);
				free_lexer(lexer);
				free(struct_free->buff);
				free_double_array(struct_free->str);
				free(struct_free->id_fork);
				free_env(envi);
				g_exit = 127;
				exit(g_exit);
			}
		}
		else if (lexer->command[i].path)
		{
			if (execve(lexer->command[i].path,
					lexer->command[i].args, env) == -1)
			{
				perror(lexer->command[i].path);
				free_lexer(lexer);
				free(struct_free->buff);
				free_double_array(struct_free->str);
				free(struct_free->id_fork);
				free_env(envi);
				g_exit = 127;
				exit(g_exit);
			}
		}
		else
		{
			ft_putstr_fd("Solo_Minishell: ", 2);
			ft_putstr_fd(lexer->command[i].token[0].data, 2);
			ft_putstr_fd(": command not found\n", 2);
			free_lexer(lexer);
			free(struct_free->buff);
			free_double_array(struct_free->str);
			free(struct_free->id_fork);
			free_env(envi);
			g_exit = 127;
			exit(g_exit);
		}
	}
}

void	exec_command(t_env *envi, t_lexer *lexer,
char **env, t_free *struct_free)
{
	int	i;
	int	fd[2048][2];

	(void)envi;
	struct_free->id_fork = NULL;
	i = 0;
	while (i <= lexer->n_command)
	{
		if (pipe(fd[i]) == -1)
			return ;
		i++;
	}
	struct_free->id_fork = (int *)malloc(sizeof(int) * lexer->n_command);
	i = 0;
	while (i < lexer->n_command)
	{
		make_redirection(&lexer->command[i], &fd, i);
		i++;
	}
	i = 0;
	while (i < lexer->n_command)
	{
		signal(SIGINT, SIG_IGN);
		if (!ft_strcmp(lexer->command[i].token[0].data, "cd"))
			built_in_cd(envi, lexer->command[i].token[1].data);
		else if (!ft_strcmp(lexer->command[i].token[0].data, "export"))
		{
			if (lexer->command[i].n_token == 1)
				built_in_env_exp(envi);
			else if (lexer->command[i].token[1].data && check_name_var(lexer->command[i].token[1].data))
				printf("export: not an identifier: %s\n" ,lexer->command[i].token[1].data);
			if (lexer->command[i].n_token > 2)
				export_error(lexer, i);
			else if (lexer->command[i].n_token == 2)
			{
				if (check_if_equal(lexer->command[i].token[1].data))
				{
					if (!check_if_in_env(envi, lexer->command[i].token[1].data))
						built_in_export(envi, lexer->command[i].token[1].data);
					else
						change_val(envi, lexer->command[i].token[1].data);
				}
				else
					add_to_export(envi, lexer->command[i].token[1].data);
			}
		}
		else if (!ft_strcmp(lexer->command[i].token[0].data, "unset")
			&& lexer->command[i].token[1].data)
			built_in_unset(envi, lexer->command[i].token[1].data);
		else if (!ft_strcmp(lexer->command[i].token[0].data, "exit")
			&& lexer->n_command < 2)
			built_in_exit(lexer, struct_free, &fd, envi);
		else
		{
			if (!ft_strcmp(lexer->command[i].token[0].data, "./minishell"))
				set_lvl(env, envi);
			struct_free->id_fork[i] = fork();
			if (struct_free->id_fork[i] < 0)
				return ;
			else if (struct_free->id_fork[i] == 0)
				treat_fork(lexer, &fd, i, env, envi, struct_free);
		}
		i++;
	}
	close_fds(&fd, lexer->n_command);
	wait_all_pid(struct_free->id_fork, lexer->n_command);
}
