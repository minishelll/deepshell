/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:31:41 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/12 13:25:13 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

int	ft_export(char **cmds, t_env *env)
{
	char	*name;
	char	*find;
	int		i;

	if (cmds[1] == NULL)
		return (ft_env(cmds, env));
	if (cmds[1][0] == '-')
		return (ft_error(error_export, not_support_option, cmds[1]));
	i = 1;
	while (cmds[i] != NULL)
	{
		find = ft_strchr(cmds[i], '=');
		if (find == NULL)
			return (ft_error(error_export, need_assignment, cmds[i]));
		name = ft_substr(cmds[i], 0, find - cmds[i]);
		if (_find_specific_char(name) != NO_SPECIFIC_CHAR)
			return (ft_error(error_export, invalid_identifier, cmds[i]));
		if (update_envlist(env->envlist, name, \
						&cmds[i][find - cmds[i] + 1]) == false)
			env->envlist = add_envlist(env->envlist, ft_strdup(cmds[i]));
		free(name);
		i++;
	}
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
		if (_find_specific_char(cmds[i]) != NO_SPECIFIC_CHAR)
			return (ft_error(error_unset, invalid_identifier, cmds[i]));
		if (find_env(env->envlist, cmds[i])[0] != '\0')
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
