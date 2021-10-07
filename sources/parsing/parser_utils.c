/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:52:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/10/01 13:31:05 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser	*init_parser(t_lexer *l)
{
	t_parser	*p;

	if (!l)
		return (NULL);
	p = malloc(sizeof(t_parser));
	if (!p)
		return (NULL);
	p->lexer = l;
	p->prev_token = NULL;
	p->curr_token = get_next_token(l);
	if (p->curr_token->type == pip)
	{
		print_msg("minishell: syntax error near unexpected token 1",
			p->curr_token->value);
		free_parser(p);
		return (NULL);
	}
	if (p->curr_token->type == illegal)
	{
		free(l->buffer);
		l->buffer = NULL;
		free_parser(p);
		return (NULL);
	}
	return (p);
}

int	is_redic(t_token *t)
{
	if (t->type == great || t->type == greater || t->type == less
		|| t->type == here_doc)
		return (1);
	return (0);
}

char	*quoted_delim(t_parser *p, char *s, int *i)
{
	char	*word;
	int		start;

	start = *i;
	while (s[*i] != 32 && s[*i] != '<')
		(*i)--;
	if (s[(*i) + 1] == DQUOTE || s[(*i) + 1] == SQUOTE)
		(*i) += 2;
	if (s[*i] == DOLLAR)
	{
		word = ft_strdup("");
		while ((s[*i] != DQUOTE || s[*i] != SQUOTE) && (*i) < start)
		{
			word = ft_joinchar(word, s[*i]);
			(*i)++;
		}
	}
	else
		word = ft_strdup(p->curr_token->value);
	return (word);
}

char	*get_stop_word(t_parser *p)
{
	int		i;
	char	*s;
	char	*word;

	i = p->lexer->curpos - 1;
	s = ft_strdup(p->lexer->buffer);
	if (p->curr_token->is_quoted == 0)
	{
		while (s[i] != 32 && s[i] != '<')
			i--;
		i += 1;
		word = ft_substr(s, i, p->lexer->curpos - i);
	}
	else
		word = quoted_delim(p, s, &i);
	free(s);
	return (word);
}

int	syntax_error(t_parser *p)
{
	if (p->prev_token->type == pip && p->curr_token->type == pip)
	{
		print_msg("minishell: syntax error near unexpected token 3",
			p->prev_token->value);
		return (0);
	}
	if ((is_redic(p->prev_token) && p->curr_token->type == eof)
		|| (p->prev_token->type == pip && p->curr_token->type == eof))
	{
		print_msg("minishell: syntax error near unexpected token `newline'\n",
			NULL);
		return (0);
	}
	return (1);
}
