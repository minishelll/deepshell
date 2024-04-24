/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_funct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:00:41 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/23 21:32:39 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "envlist.h"
#include "built_in.h"
#include "ft_error.h"
#include "libft.h"

int	ft_echo(char **cmds, t_env *env)
{
	int	opt;
	int	i;

	if (cmds[1] == NULL)
		opt = 1;
	else
		opt = ft_strncmp("-n", cmds[1], 3);
	i = 1;
	if (opt == 0)
		i = 2;
	while (cmds[i] != NULL)
	{
		char *env_tmp = find_env(env->envlist, &cmds[1][1]);
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

int	ft_cd(char **cmds, t_env *env)
{
	char	*record_cwd;
	char	*cwd;

	record_cwd = find_env(env->envlist, "PWD");
	if (record_cwd == NULL)
		record_cwd = getcwd(NULL, 0);
	//if (acess(cmds[1], F_OK) == -1)
	//	ft_error(error_cd, errno, cmds[1]);
	//	bash: cd: argu: No such file or directory
	if (chdir(cmds[1]) == -1)
		return (errno);
	if (update_envlist(env->envlist, "OLDPWD", record_cwd) == false)
		env->envlist = add_envlist(env->envlist, ft_strjoin("OLDPWD=", record_cwd));
	cwd = getcwd(NULL, 0);
	if (update_envlist(env->envlist, "PWD", cwd) == false)
		env->envlist = add_envlist(env->envlist, ft_strjoin("PWD=", cwd));
	return (0);
}

int	ft_pwd(char **cmds, t_env *env)
{
	char	*cwd;

	if (cmds[1] != NULL && cmds[1][0] == '-')
		return (ft_error(error_pwd, not_support_option, cmds[1]));
	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, 1);
	free(cwd);
	(void)env;
	return (0);
}

static int	_include_specific_char(char *str, t_bi_type bi_type)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (bi_type == bi_export \
		&& ft_isalnum(str[i]) == 0 && str[i] != '_' && str[i] != '=')
			return (SPECIFIC_CHAR_O);
		else if (bi_type == bi_unset \
		&& ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (SPECIFIC_CHAR_O);
		i++;
	}
	return (SPECIFIC_CHAR_X);
}

int	ft_export(char **cmds, t_env *env)
{
	char	*name;
	char	*find;
	int		equal_idx;
	int		i;

	i = 1;
	while (cmds[i] != NULL)
	{
		if (cmds[i][0] == '-')
		{
			if (i == 1)
				return (ft_error(error_export, not_support_option, cmds[i]));
			return (ft_error(error_export, invalid_identifier, cmds[i]));
		}
		if (_include_specific_char(cmds[i], bi_export) == SPECIFIC_CHAR_O)
			return (ft_error(error_export, invalid_identifier, cmds[i]));
		find = ft_strchr(cmds[i], '=');
		if (find == NULL)
			return (ft_error(error_export, need_assignment, cmds[i]));
		else if (cmds[i] - find == 0)
			return (ft_error(error_export, invalid_identifier, cmds[i]));
		else
		{
			equal_idx = find - cmds[i];
			name = ft_substr(cmds[i], 0, equal_idx);
			if (update_envlist(env->envlist, name, &cmds[i][equal_idx + 1]) == false)
				env->envlist = add_envlist(env->envlist, ft_strdup(cmds[i]));
			free(name);
		}
		i++;
	}
	if (cmds[1] == NULL)
		return (ft_env(cmds, env));
	return (0);
}


int	ft_unset(char **cmds, t_env *env)
{
	int	i;

	i = 1;
	while (cmds[i] != NULL)
	{
		if (cmds[i][0] == '-')
		{
			if (i == 1)
				return (ft_error(error_unset, not_support_option, cmds[i]));
			return (ft_error(error_unset, invalid_identifier, cmds[i]));
		}
		if (_include_specific_char(cmds[i], bi_unset) == SPECIFIC_CHAR_O)
			return (ft_error(error_unset, invalid_identifier, cmds[i]));
		if (find_env(env->envlist, cmds[i]) != NULL)
			delete_envlist(env->envlist, cmds[i]);
		i++;
	}
	return (0);
}

int	ft_env(char **cmds, t_env *env)
{
	int	i;

	if (cmds[1] != NULL)
	{
		if (cmds[1][0] == '-')
			return (ft_error(error_env, not_support_option, cmds[1]));
		return (ft_error(error_env, not_support_argument, cmds[1]));
	}
	i = 0;
	while (env->envlist[i] != NULL)
	{
		if (env->envlist[i][0] != '\0')
		{
					ft_putstr_fd("[", 1);
					ft_putnbr_fd(i, 1);
					ft_putstr_fd("] ", 1);
			ft_putendl_fd(env->envlist[i], 1);
		}
		i++;
	}
	return (0);
}

#include <limits.h>
static t_atol_res	try_atol(char *str, long long *result)
{
	//long long	tmp;
	int			sign;
	int			idx;

	sign = 1;
	idx = 0;
	while ((9 <= str[idx] && str[idx] <= 13) || str[idx] == 32)
		idx++;
	if (str[idx] == '-')
		sign = -1;
	if (str[idx] == '-' || str[idx] == '+')
		idx++;
	while ('0' <= str[idx] && str[idx] <= '9')
	{
		//tmp = *result;
		//if (tmp < LLONG_MAX && *result < LLONG_MAX)
		if (*result > (LLONG_MAX - (str[idx] - '0')) / 10)
			return (not_numeric);
		*result = *result * 10 + (str[idx] - '0');
		idx++;
	}
	if (str[idx] != '\0')
		return (not_numeric);
	*result *= sign;
	return (success);
}

int	ft_exit(char **cmds, t_env *env)
{
	long long	exitnum;
	t_atol_res	numeric;

	ft_putendl_fd("exit", 1);
	if (cmds[1] != NULL)
	{
		exitnum = 0;
		numeric = try_atol(cmds[1], &exitnum);
		//출력 및 exit실행
		if (numeric == not_numeric)
		{
			ft_error(error_exit, required_numeric, cmds[1]);
			exit(255);//CTRL+D처럼 처리해야되는거 아닌가?
		}
		//출력 및 $?==1
		if (numeric == success && cmds[2] != NULL)
			return (ft_error(error_exit, required_numeric, cmds[1]));
	}
	else
		exitnum = 0;
	exitnum %= 256;
	(void)env;
	exit(exitnum);//CTRL+D처럼 처리해야되는거 아닌가?
	//return (0);??
}
