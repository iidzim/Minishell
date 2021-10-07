/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 10:21:43 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/17 14:40:22 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*init_token(t_token_type type, char *s, t_lexer *l)
{
	t_token	*t;

	if (type == eof)
	{
		free(l->buffer);
		l->buffer = NULL;
	}
	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	if (s)
		t->value = ft_strdup(s);
	else
		t->value = NULL;
	t->type = type;
	t->is_quoted = l->is_quoted;
	return (t);
}

int	is_valid_id(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (!ft_isalpha(str[i]) && str[i] == '_')
			return (0);
	}
	return (1);
}

void	print_msg(char *str, char *var)
{
	printf("%s", str);
	if (var)
	{
		printf(" `");
		printf("%s", var);
		printf("'\n");
	}
	g_global->exit_status = 258;
}

int	peek_char(t_lexer *l)
{
	if (l->readpos >= l->bufsize)
		return (EOF);
	else
		return (l->buffer[l->readpos]);
}

int	multi_lines(t_lexer *l, char c)
{
	if (l->c == EOF)
	{
		if (c == DQUOTE)
			print_msg("minishell: syntax error expected \"\n", NULL);
		else
			print_msg("minishell: syntax error expected \'\n", NULL);
		l->multi_line = 1;
		return (0);
	}
	return (1);
}
