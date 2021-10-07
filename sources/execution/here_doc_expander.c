/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:05:12 by iidzim            #+#    #+#             */
/*   Updated: 2021/10/06 10:34:29 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count(t_cmd *cmd, t_token_type type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cmd->redir_nbr)
	{
		if (cmd->r[i].type == type)
			j++;
		i++;
	}
	return (j);
}

static char	*invalid_envar_here_doc(char *buff, int i)
{
	char	*s;

	s = ft_strdup("");
	if (buff[i] == '?')
		s = ft_joinfree(s, ft_itoa(g_global->exit_status));
	else
	{
		i += 1;
		while (buff[i] != '\0' && buff[i] != 32)
		{
			s = ft_joinchar(s, buff[i]);
			i++;
		}
	}
	return (s);
}

static char	*envar_helper(char *buff, int *i, char *s, int flag)
{
	char	*temp;
	char	*env;

	if (flag == 0)
	{
		temp = invalid_envar_here_doc(buff, (*i));
		(*i) += ft_strlen(temp) - 1;
		return (ft_joinfree(s, temp));
	}
	else
	{
		env = ft_strdup("");
		while (buff[*i] != '\0' && valid_envar(buff[*i]))
		{
			env = ft_joinchar(env, buff[(*i)]);
			(*i)++;
		}
		s = ft_joinfree(s, ft_getenv(env));
		free(env);
		return (s);
	}
	return (NULL);
}

char	*envar_here_doc(char *buff, int i)
{
	char	*s;

	if (!ft_strcmp(buff, "\0") || i == 1)
		return (ft_strdup(buff));
	i = -1;
	s = ft_strdup("");
	while (buff[++i] != '\0')
	{
		if (buff[i] != DOLLAR)
			s = ft_joinchar(s, buff[i]);
		else
		{
			i += 1;
			if (ft_isdigit(buff[i]) || buff[i] == '?' || !valid_envar(buff[i]))
				s = envar_helper(buff, &i, s, 0);
			else
			{
				s = envar_helper(buff, &i, s, 2);
				if (buff[i] == '\0')
					break ;
				s = ft_joinchar(s, buff[i]);
			}
		}
	}
	return (s);
}
