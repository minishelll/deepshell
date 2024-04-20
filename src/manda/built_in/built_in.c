/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:00:41 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/20 13:47:37 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "ft_error.h"
#include "built_in.h"

t_bi_type	is_built_in(char *cmdname)
{
	int			i;
	const int	len = ft_strlen(cmdname);
	char		*functlist[7] = {"echo", "cd", "pwd", "export" \
								, "unset", "env", "exit"};


	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(cmdname, functlist[i], len + 1) == 0)
			return (i);
		i++;
	}
	return (none);
}

int	execute_built_in(char **cmds, char **envlist, t_bi_type type)
{
	t_built_in	built_in_funct[7] = {ft_echo, ft_cd, ft_pwd, ft_export \
									, ft_unset , ft_env, ft_exit};

	return (built_in_funct[type](cmds, envlist));
}
