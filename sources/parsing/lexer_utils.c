/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 11:00:28 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/24 11:23:43 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_envar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*ft_getenv(char *str)
{
	char	*env_value;
	char	*env_key;
	char	*temp;
	int		i;
	int		start;

	env_value = ft_strdup("");
	i = -1;
	while (g_global->env_var[++i])
	{
		start = get_str_by_char(g_global->env_var[i], '=', 1);
		env_key = ft_substr(g_global->env_var[i], 0, start);
		if (!ft_strcmp(env_key, str))
		{
			temp = env_value;
			env_value = ft_substr(g_global->env_var[i], start + 1,
					ft_strlen(g_global->env_var[i]) - start);
			free(temp);
			ft_freeptr(env_key);
			break ;
		}
		ft_freeptr(env_key);
	}
	return (env_value);
}

char	*string_envar(t_lexer *l)
{
	char	*str;

	if (ft_isdigit(l->c))
	{
		readchar(l);
		str = ft_strdup("");
		while (l->c != EOF && !ft_strchar("|><\"\' $", l->c))
		{
			str = ft_joinchar(str, l->c);
			readchar(l);
		}
	}
	else
	{
		str = ft_strdup("$");
		while (l->c != EOF && !ft_strchar("|><\"\'$", l->c))
		{
			str = ft_joinchar(str, l->c);
			readchar(l);
		}
	}
	return (str);
}

char	*invalid_envar(t_lexer *l, int i)
{
	char	*str;
	char	*s;

	if (i == 1)
	{
		if (l->c == '0')
			str = ft_strdup("minishell");
		else if (l->c == '?')
			str = ft_itoa(g_global->exit_status);
		else
			return (string_envar(l));
		readchar(l);
		s = tokenize_text(l, str);
		free(str);
		return (s);
	}
	else
	{
		str = ft_strdup("a");
		str[0] = l->c;
		readchar(l);
		return (str);
	}
}

char	*envar_token(t_lexer *l)
{
	char	*str;
	char	*v;

	if (!l)
		return (NULL);
	if (peek_char(l) == '$' || peek_char(l) == '\"' || peek_char(l) == '\''
		|| peek_char(l) == EOF)
		return (invalid_envar(l, 0));
	readchar(l);
	if (ft_isdigit(l->c) || l->c == '?' || !valid_envar(l->c))
		return (invalid_envar(l, 1));
	str = ft_strdup("");
	while (valid_envar(l->c) && l->c != EOF)
	{
		str = ft_joinchar(str, l->c);
		readchar(l);
	}
	v = ft_getenv(str);
	free(str);
	if (!v)
		return (NULL);
	return (v);
}
