/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 20:17:30 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/10 13:39:58 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_args(t_ast *ast)
{
	int	k;

	k = 0;
	while (k < ast->args_size)
	{
		if (ast->args[k])
		{
			if (ast->args[k]->value)
				free(ast->args[k]->value);
			ast->args[k]->value = NULL;
		}
		if (ast->args[k])
			free(ast->args[k]);
		ast->args[k] = NULL;
		k++;
	}
	free(ast->args);
}

t_ast	*free_tree(t_ast *ast)
{
	int	j;

	if (!ast)
		return (NULL);
	if (ast->type == pipe_ast)
	{
		j = -1;
		while (++j < ast->pipecmd_size)
		{
			if (ast->pipecmd_values[j])
			{
				free_tree((ast->pipecmd_values[j]));
				ast->pipecmd_values[j] = NULL;
			}
		}
		free(ast->pipecmd_values);
	}
	if (ast->type == arg_ast)
		free_args(ast);
	free(ast);
	return (NULL);
}

void	free_parser(t_parser *p)
{
	free_parser2(p, 1);
	if (p->prev_token)
	{
		if (p->prev_token->value)
			free(p->prev_token->value);
		p->prev_token->value = NULL;
		free(p->prev_token);
		p->prev_token = NULL;
	}
	free(p);
}

void	free_parser2(t_parser *p, int i)
{
	if (!p)
		return ;
	if (p->lexer)
	{
		if (p->lexer->buffer)
			free(p->lexer->buffer);
		p->lexer->buffer = NULL;
		free(p->lexer);
		p->lexer = NULL;
	}
	if (p->curr_token && i == 1)
	{
		if (p->curr_token->value)
			free(p->curr_token->value);
		p->curr_token->value = NULL;
		free(p->curr_token);
		p->curr_token = NULL;
	}
}

void	free_cmd(t_cmd *z)
{
	int	i;
	int	j;

	i = -1;
	while (++i < z->nbr_cmd)
	{
		j = -1;
		while (++j < z[i].args_size)
		{
			if (z[i].argvs[j])
				free(z[i].argvs[j]);
			z[i].argvs[j] = NULL;
		}
		free(z[i].argvs);
		j = -1;
		while (++j < z[i].redir_nbr)
		{
			if (z[i].r[j].filename)
				free(z[i].r[j].filename);
			z[i].r[j].filename = NULL;
		}
		free(z[i].r);
	}
	free(z);
}
