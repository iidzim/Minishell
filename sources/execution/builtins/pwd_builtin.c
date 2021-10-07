/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:13:16 by zqadiri           #+#    #+#             */
/*   Updated: 2021/10/04 19:46:59 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	pwd_builtin(void)
{
	char	*pwd;

	g_global->exit_status = 0;
	pwd = get_env_var_by_key("PWD");
	ft_putstr_fd(pwd, 1);
	if (pwd == NULL)
	{
		pwd = getcwd(NULL, 1024);
		ft_putstr_fd(pwd, 1);
		free (pwd);
	}
	ft_putchar_fd('\n', 1);
	return (1);
}

/*
**	check lowercase
*/

int	check_builtin(t_cmd *cmd, t_data *m)
{
	char	**args;

	args = cmd->argvs;
	if (ft_strequ(args[0], "pwd"))
		return (pwd_builtin());
	else if (ft_strequ(args[0], "echo"))
		return (echo_builtin(args));
	else if (ft_strequ(args[0], "env"))
		return (env_builtin(m));
	else if (ft_strequ(args[0], "export"))
		return (export_builtin(args, m));
	else if (ft_strequ(args[0], "unset"))
		return (unset_builtin(args, m));
	else if (ft_strequ(args[0], "cd"))
		return (cd_builtin(args));
	else if (ft_strequ(args[0], "exit"))
		return (exit_builtin(args));
	return (0);
}
