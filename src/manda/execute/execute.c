/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:12:32 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/29 20:16:00 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "envlist.h"
#include "execute.h"
#include "ft_error.h"

static void	unlink_all_tmpfile(void)
{
	int	i;
	const char	*tmpfile[16] = {"/tmp/tmp1", "/tmp/tmp2", "/tmp/tmp3" \
						, "/tmp/tmp4", "/tmp/tmp5", "/tmp/tmp6", "/tmp/tmp7" \
						, "/tmp/tmp8", "/tmp/tmp9", "/tmp/tmp10" \
						, "/tmp/tmp11", "/tmp/tmp12", "/tmp/tmp13" \
						, "/tmp/tmp14", "/tmp/tmp15", "/tmp/tmp16"};

	i = 0;
	while (access(tmpfile[i], F_OK) == 0)
	{
		if  (unlink(tmpfile[i]) == -1)
			ft_error(error_systemcall, errno, NULL);
		i++;
	}
}

int	execute(t_syntax_tree *root, t_env *env)
{
	t_pipe	pipeinfo;
	int		result;

	ft_memset(&pipeinfo, 0, sizeof(t_pipe));
	if (root->type == sym_command)
		result = execute_only_command(root, env);
	else if (root->type == sym_pipe)
		result = execute_pipe(root, env, &pipeinfo);
	else if (root->type == sym_subshell)
		result = execute_subshell(root, env, NULL, parent);
	else
	{
		result = execute(root->child[L], env);
		if ((root->type == sym_and && result == 0) \
		|| (root->type == sym_or && result != 0))
			result = execute(root->child[R], env);
	}
	unlink_all_tmpfile();
	return (result);
}
