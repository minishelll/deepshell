/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_funct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:00:41 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/23 11:38:50 by taerakim         ###   ########.fr       */
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
		char *env_tmp = find_env(envlist, &cmds[1][1]);
		if (env_tmp != NULL)
			ft_putstr_fd(env_tmp, 1);
		else
			ft_putstr_fd(cmds[i], 1);
		if (cmds[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (opt != 0)
		ft_putstr_fd("\n", 1);
	return (0);
}

int	ft_cd(char **cmds, char **envlist)
{
	char	*record_cwd;
	char	*cwd;

	record_cwd = find_env(envlist, "PWD");
	if (record_cwd == NULL)
		record_cwd = getcwd(NULL, 0);
	//if (acess(cmds[1], F_OK) == -1)
	//	ft_error(error_cd, errno, cmds[1]);
	//	bash: cd: argu: No such file or directory
	if (chdir(cmds[1]) == -1)
		return (errno);
	if (update_envlist(envlist, "OLDPWD", record_cwd) == false)
		envlist = add_envlist(envlist, ft_strjoin("OLDPWD=", record_cwd));
	cwd = getcwd(NULL, 0);
	if (update_envlist(envlist, "PWD", cwd) == false)
		envlist = add_envlist(envlist, ft_strjoin("PWD=", cwd));
	return (0);
}

int	ft_pwd(char **cmds, char **envlist)
{
	char	*cwd;

	cwd = find_env(envlist, "PWD");
	if (cwd == NULL)
	{
		cwd = getcwd(NULL, 0);
		ft_putendl_fd(cwd, 1);
		free(cwd);
	}
	else
		ft_putendl_fd(cwd, 1);
	(void)cmds;
	return (0);
}

int	ft_export(char **cmds, char **envlist)
{
	//bash-3.2$ export LS=ls -l ABC =cba
	//bash: export: `-l': not a valid identifier
	//bash: export: `=cba': not a valid identifier
	
	//bash-3.2$ export LS=ls l
	//bash-3.2$ env | grep LS
	//LS=ls

	//bash-3.2$ export LS= ls
	//bash-3.2$ env | grep LS | cat -e
	//LS=$
	char	*name;
	char	*find;
	int		equal_idx;
	int		i;

	printf("export1: %p\n", envlist);
	i = 0;
	while (cmds[i] != NULL)
	{
		//if (cmds[i][0] == '-')
		//	error
		find = ft_strchr(cmds[i], '=');
		if (find != NULL)
		{
			equal_idx = find - cmds[i];
			name = ft_substr(cmds[i], 0, equal_idx);
			if (update_envlist(envlist, name, &cmds[i][equal_idx + 1]) == false)
			{
				envlist = add_envlist(envlist, cmds[i]);
				printf("export2: %p\n", envlist);
			}
			free(name);
		}
		i++;
	}
	return (0);
}

int	ft_unset(char **cmds, char **envlist)
{
	int	i;

	i = 0;
	while (cmds[i] != NULL)
	{
		if (find_env(envlist, cmds[i]) != NULL)
			envlist = delete_envlist(envlist, cmds[i]);
		i++;
	}
	return (0);
}

int	ft_env(char **cmds, char **envlist)
{
	int	i;

	//pwd: too many arguments
	if (cmds[1] != NULL)
	{
		ft_putendl_fd("env: too many arguments", 2);
		return (1);
	}
	i = 0;
	while (envlist[i] != NULL)
	{
		if (envlist[i][0] != '\0')
		{
			ft_putnbr_fd(i, 1);
			ft_putendl_fd(envlist[i], 1);
		}
		i++;
	}
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
			//echo $? -> 255
	}
	else
		exit_code = 0;
	//CTRL+D처럼 처리해야되는거 아닌가?
	exit(exit_code);
	return (0);
}
