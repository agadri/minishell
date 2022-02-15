/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconcy <sconcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:07:23 by sconcy            #+#    #+#             */
/*   Updated: 2022/02/15 14:30:29 by sconcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_slash_with_quote(char *s, int i)
{
	if (s[i] == '\"')
	{
		i++;
		while (s[i] && s[i] != '\"')
			i++;
		if (s[i] && s[i] == '\"')
			i++;
	}
	if (s[i] == '\'')
	{
		i++;
		while (s[i] && s[i] != '\'')
			i++;
		if (s[i] && s[i] == '\'')
			i++;
	}
	return (i);
}

int	is_dollar(char *s)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	if (s)
	{
		len = ft_strlen(s);
		while (i < len)
		{
			i = is_slash_with_quote(s, i);
			if (s[i] == '$')
				return (1);
			i++;
		}
	}
	return (0);
}

int	is_dollar_2(char *s)
{
	int	i;
	int	len;

	len = 0;
	i = -1;
	if (s)
	{
		len = ft_strlen(s);
		while (++i < len)
		{
			if (s[i] == '\"')
			{
				i++;
				while (i < len && s[i] != '\"')
				{
					if (s[i] == '$')
						return (1);
					i++;
				}
				if (s[i] == '\"')
					i++;
			}
		}
	}
	return (0);
}

char	*ft_join(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = (char *)malloc(len1 + len2 + 1);
	i = -1;
	while (++i < len1)
		new[i] = s1[i];
	j = 0;
	while (i < len1 + len2)
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

// char	*remove_dollar(char *str, int index, t_env *envi)
// {
// 	int		i;
// 	int		j;
// 	int		flag;
// 	int		temp;
// 	int		len;
// 	char	*path;
// 	char	*dest;
// 	char	*tmp;

// 	(void)envi;
// 	len = 0;
// 	flag = 0;
// 	temp = index + 1;
// 	j = index;
// 	i = 0;
// 	len += ft_strlen(str);
// 	while (str[index] && (str[index] != ' ' && str[index] != '\''
// 			&& str[index] != '\"' && str[index] != '$'))
// 	{
// 		index++;
// 		i++;
// 	}
// 	path = (char *)malloc(sizeof(char) * (i));
// 	if (!path)
// 		return (NULL);
// 	len -= i;
// 	i = 0;
// 	while (str[temp] && (str[temp] != ' ' && str[temp] != '\''
// 			&& str[temp] != '\"' && str[temp] != '$'))
// 	{
// 		path[i] = str[temp];
// 		temp++;
// 		i++;
// 	}
// 	path[i] = '\0';
// 	tmp = check_env(envi, path);
// 	if (!tmp)
// 	{
// 		flag = 1;
// 		tmp = (char *)malloc(sizeof(char) * (2));
// 		tmp[0] = ' ';
// 		tmp[1] = '\0';
// 	}
// 	len += ft_strlen(tmp);
// 	i = 0;
// 	temp = 0;
// 	dest = (char *)malloc(sizeof(char) * (len + 1));
// 	len = 0;
// 	if (!dest)
// 	{
// 		return (NULL);
// 	}
// 	while (len < ft_strlen(str))
// 	{
// 		if (i == j)
// 		{
// 			if (tmp)
// 			{
// 				while (tmp[temp])
// 				{
// 					dest[i] = tmp[temp];
// 					i++;
// 					temp++;
// 				}
// 				len += ft_strlen(path) + 1;
// 			}
// 			else
// 				len += ft_strlen(path) + 1;
// 		}
// 		else
// 		{
// 			dest[i] = str[len];
// 			i++;
// 			len++;
// 		}
// 	}
// 	dest[i] = '\0';
// 	free (path);
// 	free (str);
// 	if (flag == 1)
// 		free (tmp);
// 	return (dest);
// }

char *first_save(char *str, int index)
{
	int i;
	char *save;

	i = 0;
	while (str[i] && i < index)
		i++;
	save = (char *)malloc(i + 1);
	if (!save)
		return (NULL);
	i = 0;
	while (str[i] && i < index)
	{
		save[i] = str[i];
		i++;
	}
	save[i] = '\0';
	return (save);
}

char *last_save(char *str, int i)
{
	int j;
	int temp;
	char *save;

	temp = i;
	j = 0;
	while (str[i])
	{
		i++;
		j++;
	}
	save = (char *)malloc(j + 1);
	if (!save)
		return (NULL);
	j = 0;
	i = temp;
	while (str[i])
	{
		save[j] = str[i];
		i++;
		j++;
	}
	save[j] = 0;
	return (save);
}

char *remove_dollar(char *str, int index, t_env *envi)
{
	int i;
	int j;
	int len;
	char *pre_save;
	char *post_save;
	char *path;
	char *tmp;
	char *tmp2;
	
	pre_save = NULL;
	post_save = NULL;
	i = 0;
	j = index + 1;
	len = ft_strlen(str);
	if (index != 0)
		pre_save = first_save(str, index);
	while (str[j] && (str[j] != ' ' && str[j] != '\'' && str[j] != '\"' && str[j] != '$'))
	{
		j++;
		i++;
	}
	if (j < len && j > 0)
		post_save = last_save(str, j);
	path = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	j = index + 1;
	while (str[j] && (str[j] != ' ' && str[j] != '\'' && str[j] != '\"' && str[j] != '$'))
	{
		path[i] = str[j];
		j++;
		i++;
	}
	path[i] = 0;
	tmp = ft_strdup(check_env(envi, path));
	if (pre_save)
	{
		if (tmp)
		{
			tmp2= ft_strjoin(pre_save, tmp);
			free(tmp);
			tmp = ft_strdup(tmp2);
			free(tmp2);
		}
		else if (!tmp)
			tmp = ft_strdup(pre_save);
	}
	if (post_save)
	{
		if (tmp)
		{
			tmp2 = ft_strjoin(tmp, post_save);
			free(tmp);
			tmp = ft_strdup(tmp2);
			free(tmp2);
		}
		else if (!tmp)
			tmp = ft_strdup(post_save);
	}
	if (str)
		free(str);
	if (path)
		free(path);
	if (post_save)
		free (post_save);
	if (pre_save)
		free (pre_save);
	printf("COUCOU : %s\n", tmp);
	return (tmp);
}

char *remove_dollar2(char *str, int index, t_env *envi)
{
	int i;
	int j;
	int len;
	char *pre_save;
	char *post_save;
	char *path;
	char *tmp;
	char *tmp2;
	
	pre_save = NULL;
	post_save = NULL;
	i = 0;
	j = index + 1;
	len = ft_strlen(str);
	if (index != 0)
		pre_save = first_save(str, index);
	while (str[j] && (str[j] != ' ' && str[j] != '\'' && str[j] != '\"' && str[j] != '$'))
	{
		j++;
		i++;
	}
	if (j < len && j > 0)
		post_save = last_save(str, j);
	path = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	j = index + 1;
	while (str[j] && (str[j] != ' ' && str[j] != '\'' && str[j] != '\"' && str[j] != '$'))
	{
		path[i] = str[j];
		j++;
		i++;
	}
	path[i] = 0;
	tmp = ft_strdup(check_env(envi, path));
	if (pre_save)
	{
		if (tmp)
		{
			tmp2= ft_strjoin(pre_save, tmp);
			free(tmp);
			tmp = ft_strdup(tmp2);
			free(tmp2);
		}
		else if (!tmp)
			tmp = ft_strdup(pre_save);
	}
	if (post_save)
	{
		if (tmp)
		{
			tmp2 = ft_strjoin(tmp, post_save);
			free(tmp);
			tmp = ft_strdup(tmp2);
			free(tmp2);
		}
		else if (!tmp)
			tmp = ft_strdup(post_save);
	}
	if (path)
		free(path);
	if (str)
		free(str);
	if (post_save)
		free(post_save);
	if (pre_save)
		free (pre_save);
	// quote->n_quote = get_quote_number(tmp);
	// fill_quote(tmp, quote);
	return(tmp);
}

char	*treat_dollar(char *str, t_env *envi)
{
	int		i;
	char	*dest;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				i++;
			if (str[i] == '\"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			if (str[i] == '\'')
				i++;
		}
		if (str[i] == '$')
		{
			dest = remove_dollar(str, i, envi);
			return (dest);
		}
		else
			i++;
	}
	return (str);
}

int	skip_slash(char *str, int i)
{
	i++;
	while (str[i] != '\'')
		i++;
	if (str[i] == '\'')
		i++;
	return (i);
}

char	*treat_dollar_in_dquote(char *str, t_env *envi)
{
	int		i;
	char	*dest;

	i = -1;
	while (++i < ft_strlen(str))
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
			{
				if (str[i] == '$')
				{
					dest = remove_dollar(str, i, envi);
					return (dest);
				}
				i++;
			}
			if (str[i] == '\"')
				i++;
		}
		if (str[i] == '\'')
			i = skip_slash(str, i);
	}
	return (str);
}
