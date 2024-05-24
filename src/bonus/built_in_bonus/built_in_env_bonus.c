/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:31:41 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:55 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "built_in_bonus.h"
#include "ft_error_bonus.h"
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
			ft_putendl_fd(env->envlist[i], 1);
		i++;
	}
	return (0);
}
