#ifndef BUILT_IN_H
#define BUILT_IN_H

int		ft_atoi(char *str);
char	*ft_argsdup(char *str);
char	*ft_valdup(char *str);
int		is_built_in(char *cmd);
void	built_in_cd(t_lexer *lexer, char *path);
char	*ft_strcpy(char *src, char *dest);
int		built_in_echo(t_lexer *lexer);
int		take_and_cpy_env(char **env, t_lexer *lexer);
void	built_in_env(t_lexer *lexer);
void	built_in_export(t_lexer *lexer, char *var);
char	*built_in_pwd(t_lexer *lexer);
int		ft_strcmp(char *s1, char *s2);
int		del_var(char **tab, char *var);
int		built_in_unset(t_lexer *lexer, char *var);

#endif