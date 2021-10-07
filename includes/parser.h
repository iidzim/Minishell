/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:19:03 by iidzim            #+#    #+#             */
/*   Updated: 2021/10/04 19:39:24 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include "lexer.h"
# include "../libft/libft.h"

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*curr_token;
	t_token	*prev_token;
}				t_parser;

typedef struct s_index
{
	int	k;
	int	l;
	int	m;
}				t_index;

typedef enum e_ast_type
{
	pipe_ast,
	arg_ast
}			t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	struct s_ast	**pipecmd_values;
	int				pipecmd_size;
	t_token			**args;
	int				redir_nbr;
	int				args_size;
}					t_ast;

/*
** parser.c
*/

t_ast		*parse_pipe(t_parser *p);

/*
** parser_utils.c
*/

t_parser	*init_parser(t_lexer *l);
int			is_redic(t_token *t);
t_token		*check_token(t_parser *p, t_ast *ast);
int			syntax_error(t_parser *p);
char		*get_stop_word(t_parser *p);

/*
** ast.c
*/

void		init_ast(t_ast *ast, t_ast_type type);
t_cmd		*visitor(t_ast *ast);

/*
** realloc_ast.c
*/

t_token		**realloc_ast_args(t_ast *ast, int size);
t_ast		**realloc_ast_node(t_ast *ast, int size);

/*
** free.c
*/

t_ast		*free_tree(t_ast *ast);
void		free_parser(t_parser *p);
void		free_parser2(t_parser *p, int i);
void		free_cmd(t_cmd *z);

/*
** exec
*/

int			check_builtin(t_cmd *cmd, t_data *m);
int			setup_redirections(t_cmd *cmd, t_data *m);
int			execution(t_cmd *cmd, t_state *state);

#endif
