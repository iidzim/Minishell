/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 10:56:25 by iidzim            #+#    #+#             */
/*   Updated: 2021/10/05 10:52:52 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*tokenize_dquoted_text(t_lexer *l)
{
	char	*str;

	readchar(l);
	str = ft_strdup("");
	while (l->c != DQUOTE && l->c != EOF)
	{
		if (l->c == DOLLAR)
			str = ft_joinfree(str, envar_token(l));
		else
		{
			str = ft_joinchar(str, l->c);
			readchar(l);
		}
	}
	if (!multi_lines(l, DQUOTE))
	{
		free(str);
		return (NULL);
	}
	l->is_quoted = 1;
	readchar(l);
	return (str);
}

char	*tokenize_squoted_text(t_lexer *l)
{
	char	*str;

	readchar(l);
	str = ft_strdup("");
	while (l->c != SQUOTE && l->c != EOF)
	{
		str = ft_joinchar(str, l->c);
		readchar(l);
	}
	if (!multi_lines(l, SQUOTE))
	{
		free(str);
		return (NULL);
	}
	l->is_quoted = 1;
	readchar(l);
	return (str);
}

t_token	*return_token(char *str, t_lexer *l, int i)
{
	t_token	*t;

	if (i == 0)
	{
		t = init_token(id, str, l);
		free(str);
		return (t);
	}
	else
	{
		free(str);
		return (init_token(illegal, NULL, l));
	}
	return (NULL);
}

char	*quoted_string(t_lexer *l, char *str)
{
	char	*s;

	if (l->c == DQUOTE)
	{
		s = tokenize_dquoted_text(l);
		if (!ft_strcmp(s, "\0") && !ft_strcmp(str, "\0"))
			g_global->exit_status = 127;
	}
	else
	{
		s = tokenize_squoted_text(l);
		if (!ft_strcmp(s, "\0") && !ft_strcmp(str, "\0"))
			g_global->exit_status = 127;
	}
	return (s);
}

t_token	*string_token(t_lexer *l)
{
	char	*str;
	char	*s;
	char	*temp;

	str = ft_strdup("");
	while (l->curpos <= l->bufsize && l->c != PIPE && l->c != GREAT
		&& l->c != LESS && l->c != EOF)
	{
		s = ft_strdup("");
		temp = s;
		if (l->c == DQUOTE || l->c == SQUOTE)
			s = quoted_string(l, str);
		else
			s = tokenize_text(l, s);
		if (!s && l->multi_line == 1)
		{
			free(temp);
			return (return_token(str, l, 1));
		}
		str = ft_joinfree(str, s);
		free(temp);
		if (l->c == 32)
			return (return_token(str, l, 0));
	}
	return (return_token(str, l, 0));
}
