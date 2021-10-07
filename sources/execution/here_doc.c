/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:38:32 by iidzim            #+#    #+#             */
/*   Updated: 2021/10/05 19:21:58 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	random_file_name(t_data *m)
{
	static int	file_nbr = 0;
	char		*name;
	char		*itoa_nbr;
	int			fd;

	file_nbr++;
	name = NULL;
	itoa_nbr = ft_itoa(file_nbr);
	name = ft_strjoin("/tmp/file", itoa_nbr);
	free(itoa_nbr);
	m->redir->filename_ = name;
	fd = open(m->redir->filename_, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		check_valid_fd(m, m->redir->filename_, fd);
		exit (g_global->exit_status);
	}
	return (fd);
}

char	*herdoc_helper(char *buff, char *output, char *filename, int is_quoted)
{
	char	*temp;

	if (!ft_strcmp(buff, filename))
	{
		free(buff);
		return (NULL);
	}
	if (ft_strcmp(output, "\0"))
	{
		temp = output;
		output = ft_strjoin(output, "\n");
		free(temp);
	}
	output = ft_joinfree(output, envar_here_doc(buff, is_quoted));
	free(buff);
	return (output);
}

void	parse_here_doc(t_redir *r, t_data *m)
{
	char	*buff;
	char	*output;
	char	*temp;
	int		fd;
	int		empty;

	empty = 0;
	fd = random_file_name(m);
	output = ft_strdup("");
	while (1)
	{
		empty++;
		m->redir->in_heredoc = 1;
		buff = readline("> ");
		temp = output;
		output = herdoc_helper(buff, output, r->filename, r->is_quoted);
		if (!output)
			break ;
	}
	if (empty != 1)
		ft_putendl_fd(temp, fd);
	free(output);
	free(temp);
	close (fd);
}
