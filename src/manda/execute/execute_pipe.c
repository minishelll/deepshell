/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:00:57 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/18 07:19:45 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execute.h"
#include "ft_error.h"

static int	*_pipe_join(int *org, int *new, int cnt)
{
	int	*res;
	int	i;

	res = (int *)ft_malloc(sizeof(int) * (cnt * 2 + 1));
	i = 0;
	while (i < (cnt - 1) * 2)
	{
		res[i] = org[i];
		i++;
	}
	res[i] = new[0];
	res[i + 1] = new[1];
	res[i + 2] = PIPE_END;
	free(org);
	return (res);
}

static int	handle_left(t_syntax_tree *left, char **envlist, t_pipe *pipeinfo)
{
	int	result;

	result = INIT;
	if (left->type == sym_command)
		result = execute_command(left, envlist, pipeinfo, start);
	else if (left->type == sym_pipe)
		result = execute_pipe(left, envlist, pipeinfo);
	else if (left->type == sym_subshell)
		result = execute_subshell(left, envlist, pipeinfo, start);
	return (result);
}

static int	handle_right(t_syntax_tree *right, char **envlist, t_pipe *pipeinfo)
{
	int	result;

	result = INIT;
	if (right->type == sym_command)
	{
		if (pipeinfo->cnt == 1)
			result = execute_command(right, envlist, pipeinfo, end);
		else
			result = execute_command(right, envlist, pipeinfo, middle);
	}
	else if (right->type == sym_pipe)
		result = execute_pipe(right, envlist, pipeinfo);
	else if (right->type == sym_subshell)
	{
		if (pipeinfo->cnt == 1)
			result = execute_subshell(right, envlist, pipeinfo, end);
		else
			result = execute_subshell(right, envlist, pipeinfo, middle);
	}
	return (result);
}

int	execute_pipe(t_syntax_tree *curr, char **envlist, t_pipe *pipeinfo)
{
	int	curr_pipe[2];
	int	result;
	int	now_cnt;

	if (pipe(curr_pipe) == -1)
		ft_error(error_systemcall, errno, NULL);
	pipeinfo->cnt += 1;
	pipeinfo->pipelist = _pipe_join(pipeinfo->pipelist \
									, curr_pipe, pipeinfo->cnt);
	now_cnt = pipeinfo->cnt;
	result = handle_left(curr->child[L], envlist, pipeinfo);
	pipeinfo->cnt = now_cnt;
	result = handle_right(curr->child[R], envlist, pipeinfo);
	return (result);
}
