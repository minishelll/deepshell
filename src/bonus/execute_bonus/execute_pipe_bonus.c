/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:00:57 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execute_bonus.h"
#include "envlist_bonus.h"
#include "ft_error_bonus.h"

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

static int	handle_left(t_syntax_tree *left, t_env *env, t_pipe *pipeinfo)
{
	int	result;

	result = INIT;
	if (left->type == sym_command)
		result = execute_command(left, env, pipeinfo, start);
	else if (left->type == sym_pipe)
		result = execute_pipe(left, env, pipeinfo);
	else if (left->type == sym_subshell)
		result = execute_subshell(left, env, pipeinfo, start);
	return (result);
}

static int	handle_right(t_syntax_tree *right, t_env *env, t_pipe *pipeinfo)
{
	int	result;

	result = INIT;
	if (right->type == sym_command)
	{
		if (pipeinfo->cnt == 1)
			result = execute_command(right, env, pipeinfo, end);
		else
			result = execute_command(right, env, pipeinfo, middle);
	}
	else if (right->type == sym_pipe)
		result = execute_pipe(right, env, pipeinfo);
	else if (right->type == sym_subshell)
	{
		if (pipeinfo->cnt == 1)
			result = execute_subshell(right, env, pipeinfo, end);
		else
			result = execute_subshell(right, env, pipeinfo, middle);
	}
	return (result);
}

int	execute_pipe(t_syntax_tree *curr, t_env *env, t_pipe *pipeinfo)
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
	result = handle_left(curr->child[L], env, pipeinfo);
	pipeinfo->cnt = now_cnt;
	result = handle_right(curr->child[R], env, pipeinfo);
	return (result);
}
