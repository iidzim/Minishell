/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:17:57 by zqadiri           #+#    #+#             */
/*   Updated: 2021/10/05 15:07:09 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	error_retrieving_cd(void)
{
	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	printf("%s\n", strerror(errno));
}

char	*add_char_to_word(char *word, char c)
{
	char	*save_word;
	int		new_word_len;

	if (!word)
	{
		word = (char *)ft_memalloc(sizeof(char) * 2);
		if (!word)
			return (NULL);
		word[0] = c;
		word[1] = '\0';
		return (word);
	}
	new_word_len = ft_strlen_new(word) + 2;
	save_word = word;
	word = (char *)ft_memalloc(sizeof(char) * new_word_len);
	if (!word)
		return (NULL);
	ft_memcpy(word, save_word, ft_strlen_new(save_word));
	word[ft_strlen_new(save_word)] = c;
	return (word);
}

char	*get_pwd(void)
{
	char	*new_pwd;

	new_pwd = (char *)malloc(sizeof(char) * 1025);
	if (!new_pwd)
		return (NULL);
	ft_bzero(new_pwd, 1025);
	if (getcwd(new_pwd, sizeof(char) * 1024) == NULL)
	{
		free(new_pwd);
		return (NULL);
	}
	return (new_pwd);
}

char	*return_value(const char *s, int c)
{
	char	*str;
	char	val;
	int		i;

	i = ft_strlen(s);
	str = (char *)s;
	val = (char)c;
	while (i >= 0)
	{
		if (*str == val)
		{
			str++;
			return (str);
		}
		str++;
		i--;
	}
	return (NULL);
}

int	error_path(const char *cmd, const char *path, int errnum)
{
	g_global->exit_status = 1;
	printf("minishell: %s: %s: %s\n",
		cmd, path, strerror(errnum));
	return (1);
}
