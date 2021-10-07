/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 10:59:46 by zqadiri           #+#    #+#             */
/*   Updated: 2021/10/06 11:29:41 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** void rl_replace_line (const char *text, int clear_undo)
** Replace the contents of rl_line_buffer with text. The point and mark are 
** preserved, if possible.If clear_undo is non-zero,
** the undo list associated with the current line is cleared.
*/

/*
** int rl_on_new_line (void)
** Tell the update functions that we have moved onto
** a new (empty) line, usually after outputting a newline.
*/

/*
** void rl_redisplay (void) Change what's displayed 
** on the screen to reflect the current contents of rl_line_buffer.
*/

void	is_child_process(int signum)
{
		if (signum == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 1);
		else if (signum == SIGINT)
			ft_putchar_fd('\n', 1);
}

void	sigint_handler(int signum)
{
	if (g_global->pid == 0)
		is_child_process(signum);
	else
	{
		if (signum == SIGINT)
		{
			
			g_global->exit_status = 1;
			ft_putchar_fd('\n', 2);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else if (signum == SIGQUIT)
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
