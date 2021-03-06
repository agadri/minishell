#ifndef UTILS_H
#define UTILS_H

char	**ft_split(char *s, char c);
char	*ft_strdup(char *str);
char	*remove_space(char *str);
char	*ft_cpy(char *s, char c);
int		ft_strlen(char *str);
char	*ft_cpy_quoted(char *s, char c);
char	*add_space_between_redir(char *str);
void	free_double_array(char **array);
char	*ft_join(char *s1, char *s2);
int		print_error(char *str);
void	ft_putstr(char *str);
char	*ft_strchr(const char *s, int c);
char	*treat_dollar(char *str, t_env *envi);
char	*treat_dollar_in_dquote(char *str, t_env *envi);
char	*remove_dollar(char *str, int index, t_env *envi);
int		is_dollar(char *s);
int		is_dollar_2(char *s);
void	remove_all_dollar_from_command(t_command *command, t_env *envi);
void	remove_all_quote_from_command(t_command *command);
char	*remove_all_quote(char *str);
int		is_dollar_sep(char c);
int		ft_strcmp(char *s1, char *s2);
char	*remove_quote_from_limitor(char *limitor);
int		has_quote(char *limitor);
char	*remove_dollar_from_string(char *string);
int		has_slash(char *str);
int		ft_putstr_error(char *str);
int		is_str_num(char *str);
char	*check_env(t_env *envi, char *str);
int		rmove_quote1(char *str, int i, int count);
char	*rmove_quote2(char *str, int i, int count, char *dest);

#endif