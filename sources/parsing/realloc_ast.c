/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:15:34 by iidzim            #+#    #+#             */
/*   Updated: 2021/10/05 19:02:05 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*init_l(t_lexer	*l)
{
	l = malloc(sizeof(t_lexer));
	if (!l)
		return (NULL);
	l->buffer = NULL;
	l->bufsize = 0;
	l->c = ' ';
	l->curpos = 0;
	l->readpos = 0;
	return (l);
}

t_ast	**realloc_ast_node(t_ast *ast, int size)
{
	t_ast	**new;
	int		i;

	if (ast->type == pipe_ast)
	{
		new = (t_ast **)malloc(sizeof(t_ast *) * size);
		i = -1;
		while (++i < ast->pipecmd_size)
			new[i] = ast->pipecmd_values[i];
		new[i] = NULL;
		free(ast->pipecmd_values);
		ast->pipecmd_values = NULL;
		return (new);
	}
	return (NULL);
}

t_token	**realloc_ast_args(t_ast *ast, int size)
{
	t_token	**new;
	int		i;

	if (ast->type == arg_ast)
	{
		new = (t_token **)malloc(sizeof(t_token *) * (size + 1));
		i = -1;
		while (++i < size - 1)
			new[i] = ast->args[i];
		new[i] = NULL;
		free(ast->args);
		ast->args = NULL;
		return (new);
	}
	return (NULL);
}

char	*tokenize_text(t_lexer *l, char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup(s);
	while (l->c != EOF && !ft_strchar("|>< \"\'", l->c))
	{
		while (l->c == 32 && l->c != EOF)
			readchar(l);
		if (l->c == DOLLAR)
		{
			str = ft_joinfree(str, envar_token(l));
			i += 1;
		}
		else if (l->c == EOF)
			return (str);
		else
		{
			str = ft_joinchar(str, l->c);
			readchar(l);
		}
	}
	return (str);
}

t_token	*check_token(t_parser *p, t_ast *ast)
{
	char	*temp;

	if (p->curr_token->type == illegal)
		return (NULL);
	if (!syntax_error(p))
		return (NULL);
	if (is_redic(p->prev_token))
	{
		if (p->curr_token->type != id)
		{
			print_msg("minishell: syntax error near unexpected token 2",
				p->curr_token->value);
			return (NULL);
		}
		ast->redir_nbr += 1;
		if (p->prev_token->type == here_doc)
		{
			temp = p->curr_token->value;
			p->curr_token->value = get_stop_word(p);
			free(temp);
		}
	}
	return (p->curr_token);
}
