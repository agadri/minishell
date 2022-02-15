#ifndef ERRORS_H
#define ERRORS_H

int		check_quote(char *str);
int		find_next_quote(char *str, int *i);
int		find_next_dquote(char *str, int *i);
int		check_redirection_error(char *str);
int		check_parse_error(char *str);
int		put_err1(char *str, int i);
int		put_err2(char *str, int i);
int		check_quote_and_skip(char *str, int i);

#endif