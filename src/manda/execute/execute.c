/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:12:32 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/18 06:38:36 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execute.h"
#include "ft_error.h"

int	execute(t_syntax_tree *root, char **envlist)
{
	t_pipe	pipeinfo;
	int		result;

	ft_memset(&pipeinfo, 0, sizeof(t_pipe));
	if (root->type == sym_command)
		result = execute_only_command(root, envlist);
	else if (root->type == sym_pipe)
		result = execute_pipe(root, envlist, &pipeinfo);
	else if (root->type == sym_subshell)
		result = execute_subshell(root, envlist, NULL, parent);
	else
	{
		result = execute(root->child[L], envlist);
		if ((root->type == sym_and && result == 0) \
		|| (root->type == sym_or && result != 0))
			result = execute(root->child[R], envlist);
	}
	return (result);
}
