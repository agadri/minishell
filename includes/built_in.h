#ifndef BUILT_IN_H
#define BUILT_IN_H

int	init_tab(t_env **envi);
void	exec_built_in(int i, t_env *envi, t_lexer *lexer);
int		ft_atoi(char *str);
char	*ft_argsdup(char *str);
char	*ft_valdup(char *str);
int		sizetab(char **tab);
char	*ft_strjoin(char *s1, char *s2);
int		is_built_in(char *cmd);
void	built_in_cd(t_env *envi, char *path);
char	*ft_strcpy(char *src, char *dest);
int		take_and_cpy_env(t_env *envi, char **env);
void	built_in_env(t_env *env);
void	built_in_export(t_env *env, char *var);
t_tab	**copy_in_tab_unset(t_tab **tab, t_env *env, char *var);
t_tab	**copy_in_tab_export(t_tab **tab, t_env *env, char *var);
char	*built_in_pwd(t_env *envi);
void	printf_pwd(t_env *env);
int		ft_strcmp(char *s1, char *s2);
int		del_var(char **tab, char *var);
int		built_in_unset(t_env *envi, char *var);
void	free_env(t_env *env);
int		is_charspe(char *str);
int		is_num(char *str);
void	built_in_echo(int i, t_lexer *lexer);
int		is_slash(char *str);
void	built_in_exit(t_lexer *lexer, t_free *struct_free, int (*fd)[2048][2], t_env *envi);
int		exit_status(t_lexer *lexer);
int		check_if_in_env(t_env *env, char *var);
void	change_val(t_env *env, char *var);
int		check_var(char *var);
char	*ft_itoa(int nb);
void	shlvl_moins(t_env *envi);
void	shlvl_plus(t_env *envi);
void	export_error(t_lexer *lexer, int index);
int		get_shlvl(t_env *envi);
void	set_lvl(char **env, t_env *envi);
void	init_myEnv(t_env *envi);
void	built_in_env_exp(t_env *env);
int		check_name_var(char *str);
int		check_if_equal(char *str);
void	add_to_export(t_env *env, char *var);
char	*copyval(char *dup, char *str, int j);
int     check_n_echo(t_lexer *lexer, int i);
int    is_only_n(char *str);
#endif