/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_funct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:00:41 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/20 14:05:36 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "envlist.h"
#include "ft_error.h"
#include "libft.h"

int	ft_echo(char **cmds, char **envlist)
{
	int	opt;
	int	i;

	if (cmds[1] == NULL)
		opt = 1;
	else
		opt = ft_strncmp("-n", cmds[1], 2);
	i = 1;
	if (opt == 0)
		i = 2;
	while (cmds[i] != NULL)
	{
		ft_putstr_fd(cmds[i], 1);
		if (cmds[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (opt != 0)
		ft_putstr_fd("\n", 1);
	(void)envlist;
	return (0);
}

int	ft_cd(char **cmds, char **envlist)
{
	char	*cwd;

	//if (acess(cmds[1], F_OK) == -1)
	//	ft_error(error_cd, errno, cmds[1]);
	//	bash: cd: argu: No such file or directory
	if (chdir(cmds[1]) == -1)
		return (errno);
	cwd = getcwd(NULL, 0);
	if (update_envlist(envlist, "PWD", cwd) == false)
		envlist = add_envlist(envlist, ft_strjoin("PWD=", cwd));
	return (0);
}

int	ft_pwd(char **cmds, char **envlist)
{
	const char	*data = find_env(envlist, "PWD");

	(void)cmds;
	ft_putendl_fd((char *)data, 1);
	return (0);
}

int	ft_export(char **cmds, char **envlist)
{
	(void)cmds;
	(void)envlist;
	ft_putendl_fd("call ft_export", 1);
	return (0);
}

int	ft_unset(char **cmds, char **envlist)
{
	(void)cmds;
	(void)envlist;
	ft_putendl_fd("call ft_unset", 1);
	return (0);
}

int	ft_env(char **cmds, char **envlist)
{
	(void)cmds;
	(void)envlist;
	ft_putendl_fd("call ft_env", 1);
	return (0);
}

int	ft_exit(char **cmds, char **envlist)
{
	int	exit_code;

	(void)envlist;
	if (cmds[1] != NULL)
	{
		exit_code = ft_atoi(cmds[1]);
		ft_putendl_fd("exit", 1);
		//if (itoa 에 int만 있지 않은 경우는)
		//	ft_error(error_exit, ?, cmds[1]);
			//bash: exit: 3a: numeric argument required
	}
	else
		exit_code = 0;
	//CTRL+D처럼 처리해야되는거 아닌가?
	exit(exit_code);
	return (0);
}
