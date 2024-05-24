/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:00:41 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:55 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "built_in_bonus.h"
#include "ft_error_bonus.h"
#include "libft.h"

t_bi_type	is_built_in(char *cmdname)
{
	int			i;
	int			len;
	const char	*functlist[7] = {"echo", "cd", "pwd", "export" \
								, "unset", "env", "exit"};

	if (cmdname == NULL)
		return (bi_none);
	len = ft_strlen(cmdname);
	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(cmdname, functlist[i], len + 1) == 0)
			return (i);
		i++;
	}
	return (bi_none);
}

int	execute_builtin(char **cmds, t_env *env, t_bi_type type, int *redi)
{
	int					keep[2];
	int					result;
	const t_built_in	built_in_funct[7] = {ft_echo, ft_cd, ft_pwd, ft_export \
											, ft_unset, ft_env, ft_exit};

	keep[STDIN_FILENO] = dup(STDIN_FILENO);
	keep[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (redi[0] != -1)
		dup2(redi[0], STDIN_FILENO);
	if (redi[1] != -1)
		dup2(redi[1], STDOUT_FILENO);
	result = built_in_funct[type](cmds, env);
	if (redi[0] != -1)
		dup2(keep[STDIN_FILENO], STDIN_FILENO);
	if (redi[1] != -1)
		dup2(keep[STDOUT_FILENO], STDOUT_FILENO);
	close(keep[STDIN_FILENO]);
	close(keep[STDOUT_FILENO]);
	if (redi[0] != -1)
		close(redi[0]);
	if (redi[1] != -1)
		close(redi[1]);
	return (result);
}
