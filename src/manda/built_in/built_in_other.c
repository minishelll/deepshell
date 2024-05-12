/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:00:41 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/12 13:15:27 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <limits.h>
#include "envlist.h"
#include "built_in.h"
#include "ft_error.h"
#include "libft.h"

static int	_find_argument_start(char **cmds)
{
	const char	opt = 'n';
	int			cnt;
	int			i;

	i = 1;
	while (cmds[i] != NULL)
	{
		if (cmds[i][0] == '-')
		{
			cnt = 1;
			while (cmds[i][cnt] == opt)
				cnt++;
			if (cmds[i][cnt] != '\0')
				return (i);
		}
		else
			return (i);
		i++;
	}
	return (1);
}

int	ft_echo(char **cmds, t_env *env)
{
	int	arg_idx;
	int	i;

	arg_idx = _find_argument_start(cmds);
	i = arg_idx;
	while (cmds[i] != NULL)
	{
		ft_putstr_fd(cmds[i], 1);
		if (cmds[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (arg_idx == 1)
		ft_putstr_fd("\n", 1);
	(void)env;
	return (0);
}

int	ft_cd(char **cmds, t_env *env)
{
	char	*record_cwd;
	char	*cwd;

	if (cmds[1][0] == '-' && cmds[1][1] == '\0')
		return (ft_error(error_cd, not_support_option, cmds[1]));
	errno = 0;
	record_cwd = getcwd(NULL, 0);
	if (errno != 0)
		return (ft_error(error_cd, use_errno, cmds[1]));
	if (access(cmds[1], F_OK) == -1)
		return (ft_error(error_cd, no_such_file, cmds[1]));
	if (access(cmds[1], X_OK) == -1)
		return (ft_error(error_cd, permission_denied, cmds[1]));
	if (chdir(cmds[1]) == -1)
		ft_error(error_systemcall, errno, NULL);
	if (update_envlist(env->envlist, "OLDPWD", record_cwd) == false)
		env->envlist = add_envlist(env->envlist, \
									ft_strjoin("OLDPWD=", record_cwd));
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
	cwd = find_env(env->envlist, "PWD");
	if (cwd[0] == '\0')
	{
		cwd = getcwd(NULL, 0);
		if (cwd != NULL)
			ft_putendl_fd(cwd, 1);
		free(cwd);
	}
	else
		ft_putendl_fd(cwd, 1);
	return (0);
}

static t_atol_res	try_atol(char *str, long long *result)
{
	int	sign;
	int	idx;

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
		if (numeric == not_numeric)
		{
			ft_error(error_exit, required_numeric, cmds[1]);
			exit(255);
		}
		if (numeric == success && cmds[2] != NULL)
			return (ft_error(error_exit, required_numeric, cmds[1]));
	}
	else
		exitnum = env->exit_code;
	exitnum %= 256;
	exit(exitnum);
}
