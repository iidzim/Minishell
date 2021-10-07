/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:37:40 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/29 20:45:51 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*parse_args_helper(t_parser *p)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	init_ast(ast, arg_ast);
	ast->args = (t_token **)malloc(sizeof(t_token *) * 2);
	if (!ast->args)
		return (NULL);
	ast->args[1] = NULL;
	if (ast->args_size == 0)
	{
		ast->args[0] = p->curr_token;
		if (p->curr_token->type == pip)
		{
			print_msg("minishell: syntax error near unexpected token 0",
				p->curr_token->value);
			free_parser(p);
			free_tree(ast);
			return (NULL);
		}
		ast->args_size += 1;
	}
	return (ast);
}

int	init_parse_args(t_ast *ast, t_parser *p)
{
	ast->args_size += 1;
	ast->args = realloc_ast_args(ast, ast->args_size);
	p->prev_token = p->curr_token;
	p->curr_token = get_next_token(p->lexer);
	ast->args[ast->args_size - 1] = check_token(p, ast);
	if (!ast->args[ast->args_size - 1])
		return (0);
	return (1);
}

t_ast	*parse_args(t_parser *p)
{
	t_ast		*ast;

	ast = parse_args_helper(p);
	if (!ast)
		return (NULL);
	while (p->curr_token->type != eof)
	{
		if (!init_parse_args(ast, p))
			return (free_tree(ast));
		if (ast->args[ast->args_size - 1]->type == pip)
		{
			p->prev_token = p->curr_token;
			p->curr_token = get_next_token(p->lexer);
			break ;
		}
		if (ast->args[ast->args_size - 1]->type == eof)
			break ;
	}
	if (!syntax_error(p))
	{
		if (ast)
			free_tree(ast);
		return (NULL);
	}
	return (ast);
}

void	parser_multi_cmd(t_ast *ast)
{
	ast->pipecmd_size += 1;
	ast->pipecmd_values = realloc_ast_node(ast, ast->pipecmd_size + 1);
}

t_ast	*parse_pipe(t_parser *p)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	init_ast(ast, pipe_ast);
	ast->pipecmd_values = (t_ast **)malloc(sizeof(t_ast *) * 2);
	if (!ast->pipecmd_values)
		return (NULL);
	ast->pipecmd_size = 1;
	ast->pipecmd_values[ast->pipecmd_size] = NULL;
	while (p->curr_token->type != eof)
	{
		ast->pipecmd_values[ast->pipecmd_size - 1] = parse_args(p);
		if (!ast->pipecmd_values[ast->pipecmd_size - 1])
		{
			free_parser2(p, 1);
			return (free_tree(ast));
		}
		if (p->prev_token->type == pip)
			parser_multi_cmd(ast);
	}
	free_parser2(p, 0);
	return (ast);
}
