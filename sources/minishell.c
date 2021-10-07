/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/10/06 13:24:46 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize(int argc, char **argv, char **env, t_state *state)
{
	(void)argc;
	(void)argv;
	g_global = malloc(sizeof(t_global));
	if (g_global == NULL)
		exit(EXIT_FAILURE);
	dup_env_var(env);
	g_global->exit_status = 0;
	g_global->pid = 1;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	state->env_ = get_env_(env);
	state->path = NULL;
}

void	quit_minishell(void)
{
	char		*up;
	char		*ri;

	up = tgetstr("up", NULL);
	ri = tgetstr("RI", NULL);
	tputs(ri, 1, putchar);
	tputs(ri, 1, putchar);
	tputs(ri, 1, putchar);
	tputs(up, 1, putchar);
	printf("exit\n");
	exit(g_global->exit_status);
}

void	parse(t_lexer *l, t_state *state)
{
	t_cmd		*z;
	t_ast		*ast;
	t_parser	*p;

	p = init_parser(l);
	if (p)
	{
		ast = parse_pipe(p);
		if (ast)
		{
			z = visitor(ast);
			if (z)
			{
				execution(z, state);
				if (z)
					free_cmd(z);
			}
		}
	}
	if (p)
		free(p);
}

void	norme(char **buff, t_lexer **l)
{
	add_history(*buff);
	if (!is_white_space(*buff))
	{
		(*l) = init_l(*l);
		(*l)->buffer = ft_strdup(*buff);
		(*l)->bufsize = ft_strlen((*l)->buffer);
	}
	free (*buff);
}

int	main(int argc, char **argv, char **env)
{
	t_lexer		*l;
	char		*buff;
	t_state		*state;

	state = (t_state *)malloc(sizeof(t_state));
	initialize(argc, argv, env, state);
	while (1)
	{
		buff = NULL;
		buff = readline("minishell$> ");
		if (!buff)
			quit_minishell();
		else if (buff[0] == '\0')
		{
			free(buff);
			continue ;
		}
		else
		{
			l = NULL;
			norme(&buff, &l);
		}
		parse(l, state);
		system ("leaks minishell");
	}
	return (0);
}
