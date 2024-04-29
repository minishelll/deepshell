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
	return (result);
}
